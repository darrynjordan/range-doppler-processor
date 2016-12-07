#include "processor.h"


Processor::Processor(void)
{

}

void Processor::extractParameters(std::string filePath)
{
    //check that filepath is good
    std::ifstream check(filePath);

    if (!check.good())
    {
        printf("Please check .ini file path and try again.\n");
    }
    else
    {
        parameterFilePath = filePath;

        CSimpleIniA ini;
        ini.LoadFile(parameterFilePath.c_str());

        binaryFilePath 		= ini.GetValue("dataset", "filepath");
        bandwidth 			= atof(ini.GetValue("dataset", "bandwidth"));
        decimationFactor 	= atoi(ini.GetValue("dataset", "decimation_factor"));
        offset 				= atof(ini.GetValue("dataset", "adc_offset"));
        upPeriod 			= atof(ini.GetValue("dataset", "up_period"));
        downPeriod 			= atof(ini.GetValue("dataset", "down_period"));
        ns_trim 			= atoi(ini.GetValue("dataset", "trim"));
        ns_doppler			= atoi(ini.GetValue("processing", "doppler_points"));
        updateRate			= atoi(ini.GetValue("processing", "update_rate"));

        std::string keyValue = ini.GetValue("processing", "range_window");

        if (keyValue == "HAMMING")
            rangeTaper.setFunction(HAMMING);
        else if (keyValue == "HANNING")
            rangeTaper.setFunction(HANNING);
        else if (keyValue == "BLACKMAN")
            rangeTaper.setFunction(BLACKMAN);
        else
            rangeTaper.setFunction(UNIFORM);

        keyValue = ini.GetValue("processing", "doppler_window");

        if (keyValue == "HAMMING")
            dopplerTaper.setFunction(HAMMING);
        else if (keyValue == "HANNING")
            dopplerTaper.setFunction(HANNING);
        else if (keyValue == "BLACKMAN")
            dopplerTaper.setFunction(BLACKMAN);
        else
            dopplerTaper.setFunction(UNIFORM);

        keyValue = ini.GetValue("processing", "doppler");

        if ((keyValue == "1") || (keyValue == "true") || (keyValue == "TRUE"))
            isDoppler = true;
        else
            isDoppler = false;

        logger.timestamp("Dataset parameters extracted.", stopwatch);
    }
}


void Processor::perRangeProc(void)
{
	for (int i = 0; i < n_profiles; i++)
    {    
        loadBeatBuffer(i); 	
		fftBeat();		
        processPixels(rangePlot, rangeBuffer, rangeImageRow, ns_spectrum, false);  
        
        if (i%updateRate == 0)
        {
			rangePlot.plot();
			//gnuPlot.plot(rangeBuffer, ns_spectrum);
		}
        
        if (isDoppler)
        {       
			loadDopplerData(i);
			perDopplerProc(i); 
		}   
    }  
    rangePlot.save();
    logger.timestamp("Processing complete.", stopwatch);   
    cv::waitKey(0);
}


//process data extracted from the bin file into the complex rangeBuffer line by line.
void Processor::loadBeatBuffer(int index)
{
    //zero data elements
    memset(dataset, 0, ns_padded);    
    memset(beatBuffer, 0, ns_padded);  
    
    //set file pointer to start of beat
	fseek(datasetFile, (index*ns_profile + ns_trim)*sizeof(int16_t), SEEK_SET); 
    
    //read from binary file into beat buffer		
	if (fread(dataset, sizeof(int16_t), ns_profile, datasetFile) == 0)        
	{
		logger.write("Error occured while extracting binary data.");
		exit(EXIT_FAILURE);
	} 
	
	//populate beat profile and remove offset
	for (int i = 0; i < ns_profile; i++)
	{
		beatBuffer[i] = (dataset[i] - offset)*rangeTaper.getCoefficient(i);
	}
}
 

void Processor::sniffDataset(void)
{
	//assign pointer to file location
    datasetFile = fopen(binaryFilePath.c_str(), "rb");
	
	//check that file exists in the location specified
	if (datasetFile != NULL)
	{		
		//obtain file size
		fseek(datasetFile, 0, SEEK_END);
		if ((ns_dataset = ftell(datasetFile)/sizeof(int16_t)) < 0)
		{
			printf("Error reading dataset size.");
			exit(EXIT_FAILURE);
		}			
		rewind(datasetFile);	

		//adjust number of samples in dataset
		ns_dataset -= ns_trim; 

		samplingFrequency = RP_ADC_SR/decimationFactor;
		ns_profile = samplingFrequency*(upPeriod + downPeriod);
		ns_padded = nextPowTwo(ns_profile);
		ns_spectrum = ns_padded/2 + 1;
		n_profiles = floor(ns_dataset/ns_profile);
		finalDopplerIndex = (n_profiles/ns_doppler - 1)*ns_doppler;
		
		rangeTaper.generate(ns_profile);		
		dopplerTaper.generate(ns_doppler);		
		
		if(isDebug)
		{
			std::cout << std::endl;
			std::cout << "ns_trim: \t" << ns_trim << std::endl;
			std::cout << "ns_dataset: \t" << ns_dataset << std::endl;				
			std::cout << "ns_profile: \t" << ns_profile << std::endl;
			std::cout << "n_profiles: \t" << n_profiles << std::endl;
			std::cout << "ns_padded: \t" << ns_padded << std::endl;
			std::cout << "ns_spectrum: \t" << ns_spectrum << std::endl;
			std::cout << "ns_doppler: \t" << ns_doppler << std::endl;	
			std::cout << "update_rate: \t" << updateRate << std::endl;	
			std::cout << "doppler: \t" << isDoppler << std::endl;
			std::cout << std::endl;
		}
		
		logger.timestamp("Binary dataset sniffed.", stopwatch);
	}	
	else
	{
		//file does not exist in the specified location
		logger.write("Binary dataset could not be found in the specified location.");
		exit(EXIT_FAILURE);
	}
}


// produces a quick-look of the time domain beat signal
void Processor::visualize(void)
{
	char title[50];
	sprintf(title, "Doppler Buffer #%i", 10);
	
	gnuPlot.setTitle(title);
	gnuPlot.setXLabel("Sample Number");
	gnuPlot.setYLabel("Raw ADC Amplitude");
	gnuPlot.plot(dopplerImageRow, ns_doppler);
}


void Processor::allocateMemory(void)
{
	dataset = (int16_t*)malloc(ns_padded*sizeof(int16_t));		
	dopplerData = (fftw_complex*)malloc((ns_padded*ns_doppler)*sizeof(fftw_complex));
	
	beatBuffer = (double*)malloc(ns_padded*sizeof(double));	
	rangeBuffer = (fftw_complex*)malloc(ns_padded*sizeof(fftw_complex));
	dopplerBuffer = (fftw_complex*)malloc(ns_doppler*sizeof(fftw_complex));
	
	rangeImageRow = (double*)malloc(ns_spectrum*sizeof(double));
	dopplerImageRow = (double*)malloc(ns_doppler*sizeof(double));
	
	logger.timestamp("Memory allocated.", stopwatch);
}


void Processor::createPlans(void)
{	
	beatPlan    = fftw_plan_dft_r2c_1d(ns_padded, beatBuffer, rangeBuffer, FFTW_MEASURE);	
	dopplerPlan = fftw_plan_dft_1d(ns_doppler, dopplerBuffer, dopplerBuffer, FFTW_FORWARD, FFTW_MEASURE);	

	logger.timestamp("Created FFTW plans.", stopwatch);
}


void Processor::releaseMemory(void)
{
	fftw_free(rangeBuffer);
	fftw_free(dopplerBuffer);
	fftw_free(dopplerData);
	
	free(dataset);
	free(beatBuffer);
	free(rangeImageRow);
	free(dopplerImageRow);
	
	destroyPlans();
	
	fclose(datasetFile);

	logger.timestamp("Memory released.", stopwatch);
}


void Processor::destroyPlans(void)
{
	fftw_destroy_plan(beatPlan);	
	fftw_destroy_plan(dopplerPlan);
	
    logger.timestamp("Destroyed FFTW plans.", stopwatch);
}


void Processor::fftBeat(void)
{			
	fftw_execute(beatPlan);		
}


void Processor::fftDoppler(void)
{
	fftw_execute(dopplerPlan);
}

void Processor::loadDopplerData(int index)	
{
	if (index%updateRate == 0)
		dopplerIndex = index;

	if ((index - dopplerIndex) <= ns_doppler)
	{
		for (int j = 0; j < ns_padded; j++)
		{
			dopplerData[j*ns_doppler + (index - dopplerIndex)][0] = rangeBuffer[j][0];
			dopplerData[j*ns_doppler + (index - dopplerIndex)][1] = rangeBuffer[j][1];
		}
	}
}

void Processor::perDopplerProc(int index)
{	
	if ((index - dopplerIndex) == ns_doppler) //check that dopplerData is full
	{
		for (int i = 0; i < ns_spectrum; i++)		
		{
			loadDopplerBuffer(i);	
			fftDoppler();			
			processPixels(dopplerPlot, dopplerBuffer, dopplerImageRow, ns_doppler, true);	
		}	
		
		dopplerPlot.plot(); 		
	}
}


void Processor::loadDopplerBuffer(int index)
{
	for (int j = 0; j < ns_doppler; j++)
	{	
		float coefficient = dopplerTaper.getCoefficient(j);
		
		dopplerBuffer[j][0] = dopplerData[index*ns_doppler + j][0]*coefficient; 
		dopplerBuffer[j][1] = dopplerData[index*ns_doppler + j][1]*coefficient;
	}  
}


void Processor::processPixels(OpenCVPlot &outPlot, fftw_complex* inData, double* outData, int n_samples, bool isShift)
{
	double magnitude = 0.0f;
	
	for (int i = 0; i < n_samples; i++)
	{
		magnitude = 10*log(mag(inData[i]));
		
		if (isShift)
		{		
			//perform fft shift
			if (i < (n_samples/2 + 1))		
				outData[i + (ns_doppler/2 - 1)] = magnitude;
			else
				outData[i - (ns_doppler/2 + 1)] = magnitude;
		}
		else
		{
			outData[i] = magnitude;
		}
	}
	
	outPlot.addData(outData, n_samples); 
}


void Processor::initPlots(void)
{
	int rangePlot_x = 50;
	int rangePlot_y = 10;
	int dopplerPlot_x = rangePlot_x + DEFAULT_PLOT_DIM + DEFAULT_PLOT_OFFSET;
	int dopplerPlot_y = rangePlot_y;
	
	rangePlot.setSize(DEFAULT_PLOT_DIM, DEFAULT_PLOT_DIM);
    rangePlot.setPos(rangePlot_x, rangePlot_y);
    rangePlot.createWindow("RTI Plot", ns_spectrum); 
    rangePlot.setTranspose(true); 
    rangePlot.setToFile(false);
    rangePlot.setSubtract(false);
    rangePlot.setRelease(false);
    
    dopplerPlot.setSize(DEFAULT_PLOT_DIM, DEFAULT_PLOT_DIM);
    dopplerPlot.setPos(dopplerPlot_x, dopplerPlot_y);
    dopplerPlot.createWindow("Doppler Plot", ns_doppler);   
    dopplerPlot.setTranspose(false);
    dopplerPlot.setToFile(false); 
    dopplerPlot.setSubtract(false);
    dopplerPlot.setRelease(true);
    
    gnuPlot.setTitle("Range Profile");
	gnuPlot.setXLabel("Sample Number");
	gnuPlot.setYLabel("Amplitude");	
}










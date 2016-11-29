#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include "includes.h"
#include "plot.h"
#include "timer.h"
#include "taper.h"
#include "logger.h"

#define SPEED_OF_LIGHT 299792458
#define RP_ADC_SR 125e6

class Processor
{
	private:		
		//characteristics of the dataset
		FILE* datasetFile;
		
		int n_profiles;						// number of pulses in dataset 
		int ns_dataset;						// total number of samples in dataset
		int ns_profile;						// number of samples in a range-line
		int ns_padded;						// number of samples that all range-lines will be zero padded to
		int ns_spectrum;					// number of smaples in single sided range spectrum
		int ns_doppler;		
		int ns_trim;						// number of samples to trim off beginning of dataset
		int decimationFactor;				// decimation factor used to tune effective sampling frequency
		int updateRate;
		int dopplerIndex;
		int finalDopplerIndex;
		
		float upPeriod;						// time period of up-ramp [s]
		float downPeriod;					// time period of down-ramp [s]
		float offset;						// adc dc offset
		float bandwidth;					// bandwidth of transmitted signal
		float samplingFrequency;			// effective sampling frequency 
		
		const char *binaryFilePath;			// path to binary dataset
		const char *parameterFilePath;		// path to binary dataset	
		
		//buffer pointers	
		int16_t* dataset;	
		double* beatBuffer;		
		
		fftw_complex* rangeBuffer;		
		fftw_complex* dopplerData;
		fftw_complex* dopplerBuffer;
		
		double* rangeImageRow;
		double* dopplerImageRow;
		
		bool isDebug;						//enables the generation of plots at various stages of signal processing. 
		bool isDoppler;
		
		//fftw plans
		fftw_plan beatPlan;
		fftw_plan dopplerPlan;				

		GNUPlot gnuPlot;
		OpenCVPlot rangePlot;
		OpenCVPlot dopplerPlot;		
        Taper rangeTaper;
        Taper dopplerTaper;
		Logger logger;
		Timer stopwatch;
	
	public:
        Processor(const char *filePath, Timer &timer);       	

        //calculate the upper next power of two
        int nextPowTwo(float value){return (pow(2, ceil(log(value)/log(2))));};
        double mag(fftw_complex value){return sqrt(pow(value[0], 2) + pow(value[1], 2));};
		
		//memory management
		void allocateMemory(void);
		void releaseMemory(void);
		
		//data extraction
		void sniffDataset(void);
		void loadBeatBuffer(int index);
		void loadDopplerData(int index);
		void loadDopplerBuffer(int index);
		
		//plan management
		void createPlans(void);
		void destroyPlans(void);
		
		//transforms
		void fftBeat(void);
		void fftDoppler(void);
		
        //processing loop
        void perRangeProc(void);		
		void perDopplerProc(int index);				

		void processPixels(OpenCVPlot &outPlot, fftw_complex* inData, double* outData, int n_samples, bool isShift);
		
		void extractParameters(void);
		void visualize(void);
		void initPlots(void);
		 
        void setIsDebug(bool IsDebug){isDebug = IsDebug;}
        bool getIsDebug(void){return isDebug;}	
        
        void calcParameters(void);
		
		void setOffset(int Offset){offset = Offset;}
        int  getOffset(void){return offset;}
		
		void setNumProfiles(int Profiles){n_profiles = Profiles;}
        int  getNumProfiles(void){return n_profiles;}   
        
		void setNumSamplesDataset(int SamplesDataset){ns_dataset = SamplesDataset;}
        int  getNumSamplesDataset(void){return ns_dataset;}  
        
        void setTrim(int Trim){ns_trim = Trim;}
        int  getTrim(void){return ns_trim;}   
        
        void setSamplingFrequency(int Rate){samplingFrequency = Rate;}
        int  getSamplingFrequency(void){return samplingFrequency;} 
        
        void setBinaryFilePath(const char *BinaryFilePath){binaryFilePath = BinaryFilePath;}
        const char* getBinaryFilePath(void){return binaryFilePath;}           
        
        void setNumSamplesProfile(int SamplesProfile){ns_profile = SamplesProfile;}
        int  getNumSamplesProfile(void){return ns_profile;}
        
        void setNumSamplesPadded(int SamplesPadded){ns_padded = SamplesPadded;}
        int  getNumSamplesPadded(void){return ns_padded;}   
};

#endif



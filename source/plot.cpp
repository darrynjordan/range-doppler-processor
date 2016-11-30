#include "plot.h"

GNUPlot::GNUPlot(void)
{
	title = "No Title";
	xLabel = "No Label";
	yLabel = "No Label";
}


void GNUPlot::plot(int16_t *data, int samples)
{	
	FILE *gnuPipe = popen("gnuplot", "w");			
	char command[50];	
	
	//setup gnuplot
    fputs("set terminal png enhanced font 'Script,12' linewidth 0.3 \n", gnuPipe);
    
    sprintf(command, "set title '%s' \n", title);
	fputs(command, gnuPipe);
	
	sprintf(command, "set output '%s.png' \n", title);
	fputs(command, gnuPipe);
	
	sprintf(command, "set xlabel '%s' \n", xLabel);
	fputs(command, gnuPipe);
	
	sprintf(command, "set ylabel '%s' \n", yLabel);
	fputs(command, gnuPipe);	
	
	fputs("", gnuPipe);
	
	fputs("plot '-' using 1:2 lt rgb 'blue' with lines notitle\n", gnuPipe);
	
	//write data to pipe
	for (int i = 0; i < samples; i++) 
	{
		fprintf(gnuPipe, "%i %i\n", i, data[i]);
	}
	
	//close gnuplot pipe
	fputs("e\n", gnuPipe);
	pclose(gnuPipe);	
	
	//print completion message
	sprintf(command, "%s", title);
	logger.timestamp(command);	
}


void GNUPlot::plot(double *data, int samples)
{	
	FILE *gnuPipe = popen("gnuplot", "w");			
	char command[50];	
	
	//setup gnuplot
    fputs("set terminal png enhanced font 'Script,12' linewidth 0.3 \n", gnuPipe);
    
    sprintf(command, "set title '%s' \n", title);
	fputs(command, gnuPipe);
	
	sprintf(command, "set output '%s.png' \n", title);
	fputs(command, gnuPipe);
	
	sprintf(command, "set xlabel '%s' \n", xLabel);
	fputs(command, gnuPipe);
	
	sprintf(command, "set ylabel '%s' \n", yLabel);
	fputs(command, gnuPipe);	
	
	fputs("", gnuPipe);
	
	fputs("plot '-' using 1:2 lt rgb 'blue' with lines notitle\n", gnuPipe);
	
	//write data to pipe
	for (int i = 0; i < samples; i++) 
	{
		fprintf(gnuPipe, "%i %f\n", i, data[i]);
	}
	
	//close gnuplot pipe
	fputs("e\n", gnuPipe);
	pclose(gnuPipe);	
	
	//print completion message
	sprintf(command, "%s", title);
	logger.timestamp(command);	
}


void GNUPlot::plot(fftw_complex* data, int samples)
{	
	FILE *gnuPipe = popen("gnuplot", "w");			
	char command[50];	
	
	//setup gnuplot
    fputs("set terminal png enhanced font 'Script,12' linewidth 0.3 \n", gnuPipe);
    
    sprintf(command, "set title '%s' \n", title);
	fputs(command, gnuPipe);
	
	sprintf(command, "set output '%s.png' \n", title);
	fputs(command, gnuPipe);
	
	sprintf(command, "set xlabel '%s' \n", xLabel);
	fputs(command, gnuPipe);
	
	sprintf(command, "set ylabel '%s' \n", yLabel);
	fputs(command, gnuPipe);	
	
	fputs("", gnuPipe);
	
	fputs("plot '-' using 1:2 lt rgb 'blue' with lines notitle\n", gnuPipe);
	
	//write data to pipe
	for (int i = 0; i < samples; i++) 
	{
		fprintf(gnuPipe, "%i %f\n", i, sqrt(pow(data[i][0], 2) + pow(data[i][1], 2)));
	}
	
	//close gnuplot pipe
	fputs("e\n", gnuPipe);
	pclose(gnuPipe);	
	
	//print completion message
	sprintf(command, "%s", title);
	logger.timestamp(command);	
}


void GNUPlot::plot(uint8_t* data, int samples)
{	
	FILE *gnuPipe = popen("gnuplot", "w");			
	char command[50];	
	
	//setup gnuplot
    fputs("set terminal png enhanced font 'Script,12' linewidth 0.3 \n", gnuPipe);
    
    sprintf(command, "set title '%s' \n", title);
	fputs(command, gnuPipe);
	
	sprintf(command, "set output '%s.png' \n", title);
	fputs(command, gnuPipe);
	
	sprintf(command, "set xlabel '%s' \n", xLabel);
	fputs(command, gnuPipe);
	
	sprintf(command, "set ylabel '%s' \n", yLabel);
	fputs(command, gnuPipe);	
	
	fputs("", gnuPipe);
	
	fputs("plot '-' using 1:2 lt rgb 'blue' with lines notitle\n", gnuPipe);
	
	//write data to pipe
	for (int i = 0; i < samples; i++) 
	{
		fprintf(gnuPipe, "%i %i\n", i, data[i]);
	}
	
	//close gnuplot pipe
	fputs("e\n", gnuPipe);
	pclose(gnuPipe);	
	
	//print completion message
	sprintf(command, "%s", title);
	logger.timestamp(command);	
}


OpenCVPlot::OpenCVPlot(void)
{
    //set default values
    colourMapSlider = 2;
    thresholdSlider = 0;
    equalizeHistSlider = 0;
    zoomSlider = 0;
    slowSlider = 100;
    
    thresholdMax = 255;
    colourMapMax = 11; 
    zoomMax = 100; 
    slowMax = 500; 
    
    colourMapFilepath = "../media/colour_maps/0.jpg"; 
    
    isTranspose = false;
    isToFile = false;
    isSubtract = false;   
    isRelease = false;     
}


void OpenCVPlot::createWindow(std::string title, int ns_row)
{
    windowName = title;    
    rawMat = cv::Mat::zeros(1, ns_row, CV_64F);
    
    cv::namedWindow(windowName, cv::WINDOW_OPENGL);     
    cv::resizeWindow(windowName, width, height);  
    cv::moveWindow(windowName, xPos, yPos);    
    
    stringStream.str(std::string()); 
    stringStream << windowName << " Control Window";
    controlWindowName = stringStream.str();
    
    cv::namedWindow(controlWindowName);      
    cv::moveWindow(controlWindowName, xPos, yPos + height + 45);
    cv::resizeWindow(controlWindowName, width, 100);
    
    cv::createTrackbar("Zoom", controlWindowName, &zoomSlider, zoomMax, onChange, this);
    cv::createTrackbar("Slow", controlWindowName, &slowSlider, slowMax, onChange, this);
    cv::createTrackbar("Equalize Histogram", controlWindowName, &equalizeHistSlider, 1, onChange, this); 
    cv::createTrackbar("Threshold Value", controlWindowName, &thresholdSlider, thresholdMax, onChange, this);    
    cv::createTrackbar("Colour Map", controlWindowName, &colourMapSlider, colourMapMax, onChange, this);    
    
	updateColourMap();
}


void OpenCVPlot::addData(double* data, int samples)
{
    rawMat.push_back(cv::Mat(1, samples, CV_64F, data));
    currentMat = rawMat;
}


void OpenCVPlot::plot(void)
{            
    //resize the image matrix into something more display friendly             
    cv::resize(currentMat, processedMat, cv::Size(width, height));     
    //cv::normalize(currentMat, currentMat, 0, 255, cv::NORM_MINMAX);
    processedMat.convertTo(processedMat, CV_8U);
    
	cv::threshold(processedMat, processedMat, thresholdSlider, thresholdMax, 3);
    cv::threshold(colourMapMat, colourMapMat, thresholdSlider, thresholdMax, 3);
    
    if (isTranspose)
		cv::transpose(processedMat, processedMat);	

	cv::flip(processedMat, processedMat, 0); 	 
	
	if (equalizeHistSlider)
		cv::equalizeHist(processedMat, processedMat);
		
	updateColourMap();
	
    if (zoomSlider)
		processedMat = processedMat.rowRange((height*0.9)*(zoomSlider/100.0f), height);

    if (isToFile)
		save();	
		
	if (isRelease)
		rawMat.release();
	
	cv::imshow(windowName, processedMat);
	cv::waitKey(slowSlider + 1);
}


void OpenCVPlot::updateColourMap(void)
{
    //load the correct colour map image from file
    stringStream.str(std::string());    
    stringStream << COLOUR_MAP_PATH << colourMapSlider << ".jpg";
    colourMapMat = cv::imread(stringStream.str(), CV_LOAD_IMAGE_COLOR);
    
    cv::applyColorMap(processedMat, processedMat, colourMapSlider);
    
    //threshold and display the colour map
    cv::threshold(colourMapMat, colourMapMat, thresholdSlider, thresholdMax, 3);
    cv::Size size(width, COLOUR_MAP_WIDTH);   
    cv::resize(colourMapMat, colourMapMat, size);
    cv::imshow(controlWindowName, colourMapMat);
}


void OpenCVPlot::save(void)
{
	stringStream.str(std::string());	
	stringStream << SCREENSHOT_PATH << windowName << ".jpg";
	cv::imwrite(stringStream.str(), processedMat);  
	
	stringStream.str(std::string());	
	stringStream << SCREENSHOT_PATH << windowName << " CM.jpg";
	cv::imwrite(stringStream.str(), colourMapMat);
}

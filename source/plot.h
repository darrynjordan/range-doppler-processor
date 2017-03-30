#ifndef PLOT_H
#define PLOT_H

#include "includes.h"
#include "logger.h"

#define COLOUR_MAP_WIDTH 30
#define COLOUR_MAP_PATH "../media/colour_maps/"
#define SCREENSHOT_PATH "../media/screenshots/"
#define PLOT_DIM 400
#define PLOT_PADDING 5
#define PLOT_INIT_X 50
#define PLOT_INIT_Y 50

enum PlotStyle {MAGNITUDE, PHASE};

class OpenCVPlot
{
    //bit of fancy redirection to call a class-member function 'statically'
    static void onChange(int v, void *ptr)
	{
		OpenCVPlot *that = (OpenCVPlot*)ptr;
		that->plot();
	}
	
    private:
        cv::Mat rawMat;        
        cv::Mat colourMapMat;
        cv::Mat processedMat;
        cv::Mat currentMat;
        std::string windowName;
        std::string controlWindowName;
        std::string xLabel, yLabel;
        std::string colourMapFilepath;
        std::ostringstream stringStream;
        int height, width;
        int xPos, yPos;
        int equalizeHistSlider;
        int colourMapSlider;
        int thresholdSlider;
        int zoomSlider;
        int slowSlider;
        int thresholdMax;
        int colourMapMax;
        int zoomMax;  
        int slowMax; 
        bool isTranspose;
        bool isToFile; 
        bool isSubtract;  
        bool isRelease;       
        
    public:
        OpenCVPlot(void);
        void createWindow(std::string title, int ns_row);
        void addData(double* data, int samples);
        void plot(void);
        void updateThreashold(void);
        void updateColourMap(void);        
        void setSize(int Width, int Height){width = Width; height = Height;};
        void setPos(int x, int y){xPos = x; yPos = y;};
        void setXPos(int x){xPos = x;};
        void setYPos(int y){yPos = y;};
        void setWidth(int Width){width = Width; };
        void setHeight(int Height){height = Height;};  
        void setTranspose(bool choice){choice ? isTranspose = true : isTranspose = false;};
        void setToFile(bool choice){choice ? isToFile = true : isToFile = false;}; 
        void setSubtract(bool choice){choice ? isSubtract = true : isSubtract = false;};  
        void setRelease(bool choice){choice ? isRelease = true : isRelease = false;}; 
        void save(void);
};

class GNUPlot 
{
	private:
		const char* title;
		const char* xLabel;
		const char* yLabel;
		PlotStyle plotStyle;
		bool isFFTShift;
		Logger logger;
		
	public:
		GNUPlot(void);
		void plot(uint8_t *data, int samples);
		void plot(int16_t *data, int samples);
		void plot(double *data, int samples);
		void plot(fftw_complex* data, int samples);
		
		void setTitle(const char *Title){title = Title;}
        const char *getTitle(void){return title;}   
        
        void setXLabel(const char *XLabel){xLabel = XLabel;}
        const char *getXLabel(void){return xLabel;}
        
        void setYLabel(const char *YLabel){yLabel = YLabel;}
        const char *getYLabel(void){return yLabel;}      

		void setPlotStyle(PlotStyle PlotStyle);	
		void setFFTShift(bool IsFFTShift);			
};


#endif

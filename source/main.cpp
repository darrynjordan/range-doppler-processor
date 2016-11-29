#include "includes.h"
#include "processor.h"
#include "timer.h"

#define VERSION "0.1.6"

void splash(void);

int main(int argc, char *argv[])
{    
	splash();	

	if (argc != 2)
    {
		printf("Please provide a .ini file as an argument.\n");
		exit(EXIT_FAILURE);
	} 
	
	Timer stopwatch;
	stopwatch.start();	
	
	Processor processor(argv[1], stopwatch);  		
   
    processor.sniffDataset();
    processor.allocateMemory();
    processor.createPlans();  
    processor.initPlots();
    processor.perRangeProc(); 
    processor.releaseMemory();    
  
    return EXIT_SUCCESS;    
}


void splash(void)
{
	system("clear");
    printf("RDP v%s\n", VERSION);
    printf("----------------------\n");
}


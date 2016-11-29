#include "includes.h"
#include "processor.h"
#include "timer.h"
#include <unistd.h>

#define VERSION "0.1.6"

void splash(void);

int main(int argc, char *argv[])
{    
	Timer stopwatch;
	int opt;
	bool debug_flag = false;
	bool file_flag = false;
	const char *file_path;
	
	splash();	
	
	while ((opt = getopt(argc, argv, "f:d")) != -1 ) 
    {
        switch (opt) 
        {
            case 'd':
                debug_flag = true;
                break;
			case 'f':
				file_path = optarg;
				file_flag = true;
				break;
            case '?':
				if (optopt == 'f')
					fprintf (stderr, "Option -f requires an argument.\n");		
				else
				fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);				
        }
    }

	if (!file_flag)
    {
		printf("Please provide a .ini file as an argument using: -f file_name.\n");
		exit(EXIT_FAILURE);
	} 
	
	stopwatch.start();	
	
	Processor processor(file_path, stopwatch, debug_flag);  		
   
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
    printf("Range-Doppler Processor v%s\n", VERSION);
    printf("------------------------------\n");
}


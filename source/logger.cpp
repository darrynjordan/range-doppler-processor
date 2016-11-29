#include "logger.h"


Logger::Logger(void)
{
	
}

void Logger::write(std::string message)
{
	std::cout << message << std::endl;	
}


void Logger::timestamp(std::string message)
{
	cprint("[", BRIGHT, GREY);
	std::cout << timer.getTimeElapsed();	
	cprint("] ", BRIGHT, GREY);
	std::cout << message << std::endl;	
}


void Logger::timestamp(std::string message, Timer &external_timer)
{
	std::cout << "[" << std::setprecision (3) << std::fixed << external_timer.getTimeElapsed() << "] " << message << std::endl;	
}


#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "timer.h"
#include "colour.h"
#include "includes.h"

enum STYLE{WARNING, OK, ERROR, VERBOSE};

class Logger
{
	private:
		Timer timer;
		
	public:
		Logger(void);
		void write(std::string message);
		void timestamp(std::string message);
		void timestamp(std::string message, Timer &external_timer);		
};

#endif

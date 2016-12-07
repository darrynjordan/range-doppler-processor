#ifndef TIMER_HPP
#define TIMER_HPP

#include <time.h>
#include <string>

class Timer 
{
	private:
		clock_t startTime;
	
	public:		
        Timer(void);
		
		void start(void);
		float getTimeElapsed(void);
		clock_t getStartTime(void);
		std::string getTime(void);
		void setStartTime(clock_t start);
};

#endif

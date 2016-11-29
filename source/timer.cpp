#include "timer.h"


void Timer::start(void)
{
	startTime = clock();
}


float Timer::getTimeElapsed(void)
{
	return ((float)clock() - (float)startTime)/CLOCKS_PER_SEC;
}


clock_t Timer::getStartTime(void)
{
	return startTime;
}


void Timer::setStartTime(clock_t start)
{
	startTime = start;
}

std::string Timer::getTime(void)
{
  time_t rawtime;
  struct tm *timeinfo;
  char buffer [10];
  time (&rawtime);
  timeinfo = localtime (&rawtime);

  strftime (buffer,10,"%M:%S",timeinfo);
  return (std::string)buffer;
}

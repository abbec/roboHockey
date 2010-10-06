
#ifndef _CLOCK_H
#define _CLOCK_H

#include "clock.h"
#include <iomanip>
#include <sstream>

void Clock::tick()
{
	if(seconds == 0 && minutes > 0)
	{
		seconds = 59;
		minutes--;
	}
	else if(seconds > 0 && minutes >=0)
		seconds--;
}

void Clock::reset()
{
	minutes = 20;
	seconds = 0;
}

bool Clock::isEnd()
{
	return (minutes == 0 && seconds == 0);
}

std::string Clock::printTime()
{
	// Konverterar int till string
	std::stringstream out;
 	out << std::setw(2) << std::setfill('0') << minutes << ":" << std::setw(2) << std::setfill('0') << seconds;
	return out.str();
}

#endif

//
//  Timer.cpp
//  homework3
//	group 3

#include <pthread.h>
#include "Timer.h"

Timer::Timer() {
	this->time = 0;
}

string Timer::currentTime() {
	string timestr = "";
	int hour = 0;
	int minutes = this->time;
	
	// convert minute only time to hours and minutes
	while (!(minutes < 60)) {
		hour++;
		minutes -= 60;
	}
	
	// convert to appropriate string format
	timestr += to_string(hour);
	timestr += ":";
	if (minutes < 10) timestr += "0";
	timestr += to_string(minutes);
	
	return timestr;
}

void Timer::increment() {
	this->time++;
}
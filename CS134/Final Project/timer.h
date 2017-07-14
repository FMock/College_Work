#pragma once
#ifndef TIMER_H
#define TIMER_H
#include<string>
#include<sstream>

// CS134 Frank Mock

/* Timer gives objects a way to keep track of time.
*  The main game loop advances the timer and objects with a reference to timer 
*  can query it to get time values to use for game control.*/

using std::ostringstream;

struct Timer{
public:
	// time is the amount of seconds that have passed since timer started
	int time;

	inline Timer::Timer(){}

	inline Timer::Timer(int t):time(t){}

	// Advance the time
	inline void update(int ms){
		time = (ms - time) / 1000;
	}

	inline int getElapsedTime() const { return time; }

	inline std::string Timer::to_string() const{
	ostringstream oss;
	oss << "*************************\n"
		<< "Elapsed Time (sec.)= " <<  time << "\n";
		return oss.str();
	}
};
#endif
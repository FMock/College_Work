//
//  Timer.h
//  homework3
//	group 3

#pragma once
#include <iostream>
#include <unistd.h>

using namespace std;

class Timer {
	int time;
public:
	Timer();
	string currentTime();
	void increment();
};
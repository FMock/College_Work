#ifndef DAILY_H
#define DAILY_H

#include"Appointment.h"
#include<string>

using namespace std;

class Daily : public Appointment
{
public:
	Daily(string, string, string);
	bool occurs_on(int year, int month, int day);
};

#endif
#ifndef WEEKLY_H
#define WEEKLY_H

#include"Appointment.h"
#include<string>

using namespace std;

class Weekly : public Appointment
{
public:
	Weekly(string, string, string);
	virtual bool occurs_on(int year, int month, int day);
};

#endif
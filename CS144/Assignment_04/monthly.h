#ifndef MONTHLY_H
#define MONTHLY_H

#include"Appointment.h"
#include<string>

using namespace std;

class Monthly : public Appointment
{
public:
	Monthly(string, string, string);
	virtual bool occurs_on(int year, int month, int day);
};

#endif
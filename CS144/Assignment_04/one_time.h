#ifndef ONE_TIME_H
#define ONE_TIME_H

#include"Appointment.h"
#include<string>

using namespace std;

class One_Time : public Appointment
{
public:
	One_Time(string, string, string);
	bool occurs_on(int year, int month, int day);
};

#endif
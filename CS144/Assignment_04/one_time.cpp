#include<string>
#include<iostream>
#include"one_time.h"

using namespace std;

One_Time::One_Time(string desc, string aDate, string aTime) 
		: Appointment(desc, aDate, aTime){}

/*
	Determines wether the implicit date occurs on
	the same date as the date passed as parameters.
	@param aYear the year to check against
	@param aMonth the month to check against
	@param aDay the day to check against
	@returns true if it does and false otherwise
*/
bool One_Time::occurs_on(int year, int month, int day)
{
	return Appointment::occurs_on(year, month, day);
}
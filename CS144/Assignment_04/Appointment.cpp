#include<iostream>
#include<string>
#include<sstream>
#include"Appointment.h"
using namespace std;

Appointment::Appointment()
{
	description = "";
	date = "";
	time = "";
}
//Constructor that takes parameters
Appointment::Appointment(string description, string date, string time)
{
	this->description = description;
	this->date = date;
	this->time = time;
}
/*
	Determines wether an Appointment object occurs on a specific day
	@param aYear the year to check against
	@param aMonth the month to check against
	@param aDay the day to check against
	@returns true if it does and false otherwise
*/
bool Appointment::occurs_on(int aYear, int aMonth, int aDay)
{
	string aDate = intDateToString(aMonth, aDay, aYear);
	if(this->date == aDate)
		return true;
	else
		return false;
}

/*
	Static helper function that converts a numeric date into a
	string date formated as "mm dd, yyy".
	@param month the integer that is a month
	@param day the integer that is a day
	@param year the integer that is a year
	@return a formated string representation of the date
*/
string Appointment::intDateToString(int month, int day, int year)
{
	ostringstream outstr;
	string theMonth;

	enum MonthsOfYear{January = 1, February = 2, March = 3, April = 4,
					  May = 5, June = 6, July = 7, August = 8,
					  September = 9, October = 10, November = 11, December = 12};
	switch(month)
	{
	case January: theMonth = "January";
		break;
	case February: theMonth = "February";
		break;
	case March: theMonth = "March";
		break;
	case April: theMonth = "April";
		break;
	case May: theMonth = "May";
		break;
	case June: theMonth = "June";
		break;
	case July: theMonth = "July";
		break;
	case August: theMonth = "August";
		break;
	case September: theMonth = "September";
		break;
	case October: theMonth = "October";
		break;
	case November: theMonth = "November";
		break;
	case December: theMonth = "December";
		break;
	default: theMonth = "";
	}

	outstr << theMonth << " " << day << ", " << year;
	return outstr.str();
}
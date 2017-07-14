#include<string>
#include<iostream>
#include"Appointment.h"
#include"monthly.h"

using namespace std;

//Constructor
Monthly::Monthly(string desc, string aDate, string aTime) 
		: Appointment(desc, aDate, aTime){}
/*
	Compares wether the implicit appointment object
	is in the same month as the explicit date.
	@param aYear the year to check against
	@param aMonth the month to check against
	@param aDay the day to check against
	@return true if in the same month, false otherwise
*/
bool Monthly::occurs_on(int aYear, int aMonth, int aDay)
{
	//validate input and get date as string
	string aDate = intDateToString(aMonth, aDay, aYear);
	int i = aDate.find(" ");
	string month1 = aDate.substr(0, i);
	int j = this->get_date().find(" ");
	string month2 = this->get_date().substr(0, j);
	//if each month is the same return true
	if(month1 == month2)
		return true;
	else
		return false;
}
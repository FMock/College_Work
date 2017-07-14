#include<string>
#include<sstream>
#include<iostream>
#include"daily.h"

using namespace std;
/*
	Constructor
*/
Daily::Daily(string desc, string aDate, string aTime) 
		: Appointment(desc, aDate, aTime){}


/*
	Compares wether the implicit appointment object
	is on the same day as the explicit date.
	@param aYear the year to check against
	@param aMonth the month to check against
	@param aDay the day to check against
	@return true if on the same day, false otherwise
*/
bool Daily::occurs_on(int aYear, int aMonth, int aDay)
{
	//validate input and extract day
	string aDate = intDateToString(aMonth, aDay, aYear);
	int i = aDate.find(" ");
	int j = aDate.find(",");
	string day1 = aDate.substr(i + 1, j - i - 1);
	int k = this->get_date().find(" ");
	int m = this->get_date().find(",");
	string day2 = this->get_date().substr(k + 1, m - k - 1);
	istringstream iss(day1);
	int d1;
	iss >> d1;
	istringstream iss2(day2);
	int d2;
	iss2 >> d2;
	if(d1 == d2)
		return true;
	else
		return false;
}
#include<string>
#include<sstream>
#include<iostream>
#include"weekly.h"

using namespace std;

Weekly::Weekly(string desc, string aDate, string aTime) 
		: Appointment(desc, aDate, aTime){}

/*
	Compares wether the implicit appointment object
	is in the same week as the explicit date.
	@param aYear the year to check against
	@param aMonth the month to check against
	@param aDay the day to check against
	@return true if in the same week, false otherwise
*/
bool Weekly::occurs_on(int aYear, int aMonth, int aDay)
{
	//validate input and extract day of week
	string aDate = intDateToString(aMonth, aDay, aYear);
	int i = aDate.find(" ");
	int j = aDate.find(",");
	string weekDay1 = aDate.substr(i + 1, j - i - 1);
	int k = this->get_date().find(" ");
	int m = this->get_date().find(",");
	string weekDay2 = this->get_date().substr(k + 1, m - k - 1);

	//convert week day strings to integers
	istringstream iss(weekDay1);
	int d1;
	iss >> d1;
	istringstream iss2(weekDay2);
	int d2;
	iss2 >> d2;
	//see if both days are in the same week
	int week1 = 7; int week2 = 14; int week3 = 21; int week4 = 31;
	if(week1 - d1 >= 0 && week1 - d2 >= 0)//both dates occur in the first week
		return true;
	if(week2 - d1 >= 0 && week2 - d2 >= 0)//both dates occur in the second week
		return true;
	if(week3 - d1 >= 0 && week3 - d2 >= 0)//both dates occur in the third week
		return true;
	if(week4 - d1 >= 0 && week4 - d2 >= 0)//both dates occur in the last week
		return true;
	else
		return false;
}
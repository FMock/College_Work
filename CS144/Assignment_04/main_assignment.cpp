#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include"Appointment.h"
#include"one_time.h"
#include"daily.h"
#include"weekly.h"
#include"monthly.h"

/*
	CS144
	Assignment 4 Exercise P8.7
	Frank Mock
*/
using namespace std;

//Helper functions
bool dateIsValid(int month, int day, int year);
string getDateString(int month, int day, int year);
int str_to_int(string s);

int main()
{
	string description, date, time_of_day, time;
	string inputMonth, inputDay, inputYear, inputHour, inputMin, inputType;
	int month, day, year, hour, minutes, type;
	vector<Appointment*> appointments;
	string moreInput = "y";

	//Enter Appointments
	do
	{
		cout << "What Type of Appointmnet? Select [1 - 4]" << endl;
		cout << "[1] One Time" << endl;
		cout << "[2] Daily" << endl;
		cout << "[3] Weekly" << endl;
		cout << "[4] Monthly" << endl;
		getline(cin, inputType);
		istringstream inss(inputType);
		inss >> type;
		cout << "Enter brief appointment description: ";
		string description;
		getline(cin, description);
		tryAgain://return hear if the date is invalid
		cout << "Enter date using the following format: mm dd yyyy ";
		cin >> inputMonth >> inputDay >> inputYear;
		//convert string inputMonth to integer
		if(str_to_int(inputMonth) < 0)
			goto tryAgain;
		else
			month = str_to_int(inputMonth);
		//convert string inputDay to integer
		if(str_to_int(inputDay) < 0)
			goto tryAgain;
		else
			day = str_to_int(inputDay);
		//convert string inputYear to integer
		if(str_to_int(inputYear) < 0)
			goto tryAgain;
		else
			year = str_to_int(inputYear);
		//Check if the date is a valid date
		if(!dateIsValid(month, day, year))
			goto tryAgain;
		//get a string representation of the valid date
		date = getDateString(month, day, year);
		EnterTime://start here if invalid time is entered
		cout << "Enter time of appointment hh mm ";
		cin >> inputHour >> inputMin;
		//convert string inputHour to integer
		if(str_to_int(inputHour) < 0)
			goto EnterTime;
		else
			hour = str_to_int(inputHour);
		//convert string input minutes to integer
		if(str_to_int(inputMin) < 0)
			goto EnterTime;
		else
			minutes = str_to_int(inputMin);
		//check for valid hour and minutes
		if(hour < 1 || hour > 12)
		{
			cout << "Hours must be between 1 - 12" << endl;
			goto EnterTime;
		}
		if(minutes < 0 || minutes > 59)
		{
			cout << "Minutes must be between 0 - 59" << endl;
			goto EnterTime;
		}
		string rem;
		getline(cin, rem);
		TimeOfDay://return here if invalid time of day
		cout << "am or pm ? ";
		cin >> time_of_day;
		if(time_of_day != "am")
			if(time_of_day != "pm")
				goto TimeOfDay;

		time = inputHour + ":" +  inputMin + " " + time_of_day;

		//add appointment to vector of appointments
		switch(type)
		{
		case 1:	appointments.push_back(new One_Time(description, date, time));
			break;
		case 2: appointments.push_back(new Daily(description, date, time));
			break;
		case 3: appointments.push_back(new Weekly(description, date, time));
			break;
		case 4: appointments.push_back(new Monthly(description, date, time));
			break;
		}
		//appointments.push_back(new Appointment(description, date, time));
		cout << "Would you like to enter another appointment? (y/n) ";
		cin >> moreInput;
		string remainder;
		getline(cin, remainder);
	}while(moreInput == "y");

	//Ask for a date and disply the appointments on that date
	GetDate:
	cout << "Display all appointments for what date? mm dd yyyy ";
	cin >> inputMonth >> inputDay >> inputYear;
	//convert string inputMonth to integer
	if(str_to_int(inputMonth) < 0)
		goto GetDate;
	else
		month = str_to_int(inputMonth);
	//convert string inputDay to integer
	if(str_to_int(inputDay) < 0)
		goto GetDate;
	else
		day = str_to_int(inputDay);
		//convert string inputYear to integer
	if(str_to_int(inputYear) < 0)
		goto GetDate;
	else
		year = str_to_int(inputYear);
	//Check if the date is a valid date
	if(!dateIsValid(month, day, year))
		goto GetDate;
	//get a string representation of the valid date
	date = getDateString(month, day, year);
	cout << "Here are the appointments on " << date << endl;
	for(unsigned int i = 0; i < appointments.size(); i++)
	{
		Appointment a = *appointments[i];
		if(a.occurs_on(year, month, day))
		{
			cout << a.get_description() << " " << a.get_date() << " " << a.get_time() << endl;	
		}
	}
	cout << endl;
	cout << "Type any key to end";
	string end;
	cin >> end;
	return 0;
}

/*
	Checks wether the numeric date representation is valid
	@param month the month
	@param day the day
	@param year the year
	@return false if numeric date is invalid true otherwise
*/
bool dateIsValid(int month, int day, int year)
{
	enum MonthsOfYear{January = 1, February = 2, March = 3, April = 4,
					  May = 5, June = 6, July = 7, August = 8,
					  September = 9, October = 10, November = 11, December = 12};
	//Compute days in February
	int daysInFebruary;
	if((year % 4) != 0)
		daysInFebruary = 28;
	else if((year % 400) == 0)
		daysInFebruary = 29;
	else if((year % 100) == 0)
		daysInFebruary = 28;
	else
		daysInFebruary = 29;
	//if month is valid, determine how many days it has
	int daysInMonth;
	switch(month)
	{
	case January: case March: case May: case July: 
	case August: case October: case December:
		daysInMonth = 31;
		break;
	case April: case June: case September:
	case November:
		daysInMonth = 30;
		break;
	case February:
		daysInMonth = daysInFebruary;
		break;
	default:
		cout << "Invalid month: " << month << endl;
		return false;
	}

	//determine if the day is valid
	if((day < 1) || (day > daysInMonth))
	{
		cout << "Invalid day of month " << day << endl;
		return false;
	}
	return true;
}

/*
	Get a string representation of a numeric date
	@param month the integer that represents the month
	@param day the integer that represents the day
	@param year the integer that represents the year
	@return a string representation of the date
*/
string getDateString(int month, int day, int year)
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

/*
	Converts a string that represents a positive integer into a positive integer
	@param s the string representation of a number
	@return the number representation or -1 if failed attempt
*/

int str_to_int(string s)
{
	istringstream iss(s);
	int n;
	if(iss >> n)
		return n;
	else
	{
		cout << "Error converting " << s << " to integer" << endl;
		return -1;
	}
}
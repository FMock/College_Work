#ifndef APPOINTMENT_H
#define APPOINTMENT_H
#include<string>

using namespace std;

class Appointment
{
public:
	Appointment();

	Appointment(string description, string date, string time);

	string get_description()const {return description;}
	void set_description(string description){description = description;}
	string get_date() const{return date;}
	void set_date(string aDate){date = aDate;}
	string get_time()const{return time;}
	void set_Time(string atime){time = atime;}
	virtual bool occurs_on(int year, int month, int day);
	static string intDateToString(int month, int day, int year);

private:
	string description;
	string date;
	string time;
};

#endif
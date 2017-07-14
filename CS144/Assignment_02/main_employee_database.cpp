#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>

using namespace std;
#include "employee.h"

/*
	CS144 Assignment #2
	Frank Mock

	This program uses a text file called "data.txt" This file is included 
	with the source code. Some names in data.txt are Frank Mock, Debbie Mock,
	Fred Flintstone, Fred Rogers, Debbie Hunter and more (10 total employees). 
	
	This program also uses the employee class from
	the textbook. Program 9.6 was used as a starting point for this
	assignment.
	First the program asks the user for the employee data file.
	Next, the program asks the user for a first and last name of an employee
	to search for. If found the program will ask if you wish to search again.
	If the user does not want to search again, a menu of options is displayed
	to the user as per the assignment instructions.
	When option 2 is chosen and you are viewing the last employee in the file,
	the last employee will be re-displayed to the user.
*/

const int NEWLINE_LENGTH = 2;
//name field is 30 characters
const int NAME_SIZE = 30;
//salary field is 10
const int SALARY_SIZE = 10;
//total length of a single employee record
const int RECORD_SIZE = NAME_SIZE + SALARY_SIZE + NEWLINE_LENGTH;
//Number of records in file
int num_records = 0;

/**
	Converts a string number into a double value
	@param s is the string to be converted
	@return the double representation of the string number
*/
double string_to_double(string s)
{
	istringstream instr(s);
	double x;
	instr >> x;
	return x;
}

/*
	Raises an employee salary
	@param e reference to employee variable
	@param percent the percentage to raise employee salary
*/
void raise_salary(Employee& e, double percent)
{
	double new_salary = e.get_salary() * (1 + percent / 100);
	e.set_salary(new_salary);
}

/*
	Reads an employee record from a file at the current
	position of the get pointer.
	@param e Employee ready to be instantiated
	@param in the stream to be read from
*/
void read_employee(Employee& e, istream& in)
{
	string line;
	getline(in, line);
	if(in.fail())
		return;
	string name = line.substr(0,NAME_SIZE);
	double salary = string_to_double(line.substr(NAME_SIZE, SALARY_SIZE));
	e = Employee(name, salary);
}

/*
	Writes an Employee record to a stream
	@param e the employee record to write
	@param out the stream to write to
*/
void write_employee(Employee& e, ostream& os)
{
	os << e.get_name()
		<< setw(SALARY_SIZE + (NAME_SIZE - e.get_name().length()))
		<< fixed << setprecision(2)
		<< e.get_salary();
}

/*
	Performs a case insensitive comparison of two C strings
	@param *s1 C string on the left
	@param *s2 C string on the right
	@return -1 if left is greater and 1 other wise. 0 if equal
*/
int strcmp_ignore_case(const char *s1, const char *s2)
{
	while(*s1 && *s2)
	{
		if(tolower(*s1) != tolower(*s2))
			break;
		++s1;
		++s2;
	}
	return tolower(*s1) - tolower(*s2);
}

/*
	Searches a file for a record that matches the first and last name
	@param fs a reference to a fstream object
	@param first employee first name to be searched for
	@param last employee last name to be searched for
	@return record number that matches employee or -1 if not found
*/
int get_record_num(fstream& fs, string first, string last)
{
	char input[RECORD_SIZE]; //to hold the input from the file
	int counter = 0;
	fs.seekg(0 * RECORD_SIZE, ios::beg);
	while(!fs.eof())
	{
		string f_name, l_name;
		fs.getline(input, RECORD_SIZE);
		string fullname(input,0, NAME_SIZE);
		int k = fullname.find(",");
		int r = fullname.find(" ",k + 2);
		int l = fullname.length();
		if(l > 0)
		{
			l_name = fullname.substr(0,k);
			f_name = fullname.substr(k+2, r - (k+2));
			if(strcmp_ignore_case(first.c_str(), f_name.c_str()) == 0 
				&& strcmp_ignore_case(last.c_str(), l_name.c_str()) == 0)
				return counter;
		}
		counter++;
	}
	fs.clear(); //clear EOF flag
	return -1; //not found
}


int main()
{
	Employee e; //to hold an employee object
	const double SALARY_CHANGE = 5.0;//percent to change salary
	int num_records;//number of employee records
	int position;//current position on file position pointer
	bool tryAgain = true;//for loop control top
	bool more = true;//for loop control bottom
	fstream fs;//input and output
	string dataFile;
	string first, last, again;

	do{
		cout << "Please enter the data file name: ";
		cin >> dataFile;

		//try to open the file
		fs.open(dataFile.c_str());
		if(fs.fail())
		{
			string again;
			cout << "Problem opening data file or it does not exist. Try Again? (y/n)";
			cin >> again;
			if(again != "y")
				tryAgain = false;
		}
		else
		{
			cout << "Data file opened successfully." << endl;
			tryAgain = false;
		}

	}while(tryAgain);

	top://return here from lower menu case: 3

	//determine the number of records in the data file
	fs.seekg(0, ios::end);
	num_records = static_cast<int>(fs.tellg()) / RECORD_SIZE;
	//position get pointer at the begining of the file
	fs.seekg(0, ios::beg);

  bool query = true; //used forthe following do-while loop

  do{
		//Ask the user for an employee to display
		cout << "Enter employee First name: ";
		cin >> first;
		cout << "Enter employee Last name: ";
		cin >> last;

		//search for employee record number
		position = get_record_num(fs, first, last);
		if(position < 0)
		{
			cout << first << " " << last << " was not found." << endl;
			query = true;
		}
		else
		{
			fs.clear();
			//position the get pointer at the begining of the employee record
			fs.seekg(position * RECORD_SIZE, ios::beg);
			//reads employee record and instantiates Employee object using this record
			read_employee(e, fs);
			cout << endl;
			cout << "Record #" << position << " " << e.get_name() << " " << e.get_salary() << endl;
			cout << endl;
		}
		//clear the cin buffer
		string remainder;
		getline(cin, remainder);
		cout << "Search Again? (y/n)";
		cin >> again;
		if(again != "y")
			query = false;

	}while(query);

  /*
	At this point an employee record the user wants to work with has been found.
	Now show menu with further options. Each option is a different case.
  */
	query = true; // for do-while loop control

	do
	{
		int choice;
		cout << "Please choose [1 -4]" << endl;
		cout << "[1] Change salary of this record" << endl;
		cout << "[2] View next record" << endl;
		cout << "[3] Find another employee" << endl;
		cout << "[4] Quit" << endl;
		cin >> choice;
		
		switch(choice)
		{
			case 1: fs.clear();
					//position the get pointer at the employee record
					fs.seekg(position * RECORD_SIZE, ios::beg);
					//reads employee record and instantiates Employee object using this record
					read_employee(e, fs);
					//raise the salary of the employee by a certain percent
					raise_salary(e, SALARY_CHANGE);
					//update the employee data file
					fs.seekp(position * RECORD_SIZE, ios::beg);
					write_employee(e, fs);
					//display the new salary of the employee
					cout << endl;
					cout << "The new salary is: " << e.get_salary() << endl;
					cout << endl;
					query = true;
					break;

			case 2: fs.clear();
					if(position != num_records)//check to ensure we don't go past EOF
						position = position + 1;
					//position the get pointer at the begining of the employee record
					fs.seekg(position  * RECORD_SIZE, ios::beg);
					//reads employee record and instantiates Employee object using this record
					read_employee(e, fs);
					cout << endl;
					cout << "Record #" << position << " " << e.get_name() << " " << e.get_salary() << endl;
					cout << endl;
					query = true;
					break;

			case 3:	goto top;


			case 4:	query = false;
					break;

		}
		string remainder;
		getline(cin, remainder);
	}while(query);

	//Close the data file
	fs.close();

	return 0;
}
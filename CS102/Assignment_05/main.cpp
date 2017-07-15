//CS_102 Begining Programming C++
//Assignment #5  'Days Out'
//Programmer: Frank Mock
//Program Description: This program calculates the average number of days
//                     a company's employees are absent

#include<iostream>
#include<iomanip>
using namespace std;

//Function prototypes
int numberOfEmployees();
int daysAbsent(int);
double avgDaysAbsent(int, int);


int main()
{
    //Initialize local variables
    int employeeCount;
    int totalAbsent;
       
    //Welcome user to program
    cout << "Welcome to the Employee Average Days Absent Program\n";
    cout << "---------------------------------------------------\n\n";
    
    //Get number of employees by calling numberOfEmployee function
    employeeCount = numberOfEmployees();
    //Get total days absent by calling daysAbsent function
    totalAbsent = daysAbsent(employeeCount);
    //Display the results
    cout << "\nTotal number of employees: " << employeeCount << endl;
    cout << "Total days absent: " << totalAbsent << endl;
    cout << fixed << showpoint << setprecision(2);
    cout << "The average number of days absent is: " << avgDaysAbsent(employeeCount, totalAbsent) << endl;
    system("pause");
    return 0;
}

//*****************************************************************
//This function gets the number of employees from the user and    *
//and returns this value to the function call in main             *
//*****************************************************************
int numberOfEmployees()
{
    int numEmployees = 0;
    
    //Get the number of employees from the user
    do
    { 
        cout << "Please enter the number of employees: ";
        cin >> numEmployees;
    }while(numEmployees < 1);
    return numEmployees;   
}

//******************************************************************
//This function gets the number of days missed for each employee   *
//and returns the total number of days absent for all              *
//******************************************************************
int daysAbsent(int numberOfEmployees)
{
    int totalDaysAbsent = 0;
    int missed = 0;
    
    //Get number of days absent for each employee
    for(int i = 0; i < numberOfEmployees; i++)
    {
        do
        {     
            cout << "Enter the number of days absent for employee #" << i + 1 << ": ";
            cin >> missed;
        }while(missed < 0);
        
        //Keep a total of the number of days absent for all employees
        totalDaysAbsent += missed;  
    }
    return totalDaysAbsent; 
}

//******************************************************************
//This function returns as a double the average number of days     *
//absent. It takes two integers as arguments, one represents the   *
//total number of employees and the other the total days absent for*
//all employees                                                    *
//******************************************************************
double avgDaysAbsent(int numEmployees, int totalAbsent)
{
    //Calculate the average number of days absent and return number
    return totalAbsent / static_cast<double>(numEmployees); 
}

//CS_102 Begining Programming C++
//Assignment #9 Course Grade
//Programmer: Frank Mock
//Program Description: This program will gather test score data for a
//group of students and store the info in a structure.
//Each structur'e "tests" member points to a
//dynamically allocated array that holds the test scores.

#include<iostream>
#include<iomanip>
using namespace std;

const int NAME_LENGTH = 25;

//Define structure
struct GradeInfo
{
    char name[NAME_LENGTH];
    int idNum;
    int *tests;
    float average;
    char grade;
};

//Function prototype
void getData(GradeInfo *, int, int);
void getAverage(GradeInfo *, int, int);
void getLetterGrade(GradeInfo *, int);

int main()
{
    //Define variables
    int numStudents;
    int numTestScores;
    
    cout << "Welcome to the Course Grade Program" << endl;
    cout << "***********************************" << endl;
    
    //Get the number of students accept a reasonable range between 0 and 5000
    do
    {
    cout << "How many students? ";
    cin >> numStudents;
    }while(numStudents < 0 || numStudents > 5000);
    
    //Get the number of test scores accept a reasonable range between 1 and 25
    do
    {
    cout << "How many test scores? ";
    cin >> numTestScores;
    }while(numTestScores < 1 || numTestScores > 25);
    
    //Dynamically allocate a pointer of GradeInfo structures
    GradeInfo *studentGrade;
    studentGrade = new GradeInfo[numStudents];
        
    //Dynamically allocate memory address for pointer member tests
    for(int i = 0; i < numStudents; i++)
    {
        studentGrade[i].tests = new int[numTestScores];
    }
    
    //Call the getData function
    getData(studentGrade, numStudents, numTestScores);
    
    //Setup output formatting
    cout << setprecision(3);
    
    //Fill additional members and display results
    for(int j = 0; j < numStudents; j++)
    {   
        cout << "\nStudent #" << j + 1 << endl;
        cout << "Name: " << studentGrade[j].name << endl;
        cout << "ID Number: " << studentGrade[j].idNum << endl;
        for(int k = 0; k < numTestScores; k++)
        {
            cout << "Score #" << k + 1 << " : " << studentGrade[j].tests[k] << endl; 
        }
        
        //Assign average structure member and display student average
        getAverage(studentGrade, j, numTestScores);
        cout << "Average: " << studentGrade[j].average<< endl;
        
        //Assign grade structure member and display student grade
        getLetterGrade(studentGrade, j);
        cout << "Letter Grade: " << studentGrade[j].grade<< endl; 
    }
 
    system("pause");
    return 0;
}

//***********************************************************
//Definition for function getData                           *
//This function will gather data from the user and fill     *
//the pointer structure member tests with the values        *
//***********************************************************
void getData(GradeInfo *gd, int size, int numScores)
{  
    for(int i = 0; i < size; i++)
    {
        cout << "\nStudent #" << i + 1 << endl;
        //Get the student name
        cout << "Enter name: ";
        cin.ignore();
        cin.getline(gd[i].name, NAME_LENGTH);
        
        //Get the student ID number
        cout << "Enter ID number: ";
        cin >> gd[i].idNum;
        
        //Get test scores between 0 and 100
       for(int count = 0; count < numScores; count++)
       {
           do
           {        
           cout << "Enter #" << count + 1 << " test score ";
           cin >> gd[i].tests[count];
           }while(gd[i].tests[count] < 0 || gd[i].tests[count] > 100); 
       }
    }    
}

//*****************************************************************
//Definition for function getAverage                              *
//This function will total each students test results and         *
//compute the average. It will then assign the average to the     *
//average member of the GradeInfo structure pointer               *
//*****************************************************************
void getAverage(GradeInfo *gd, int student, int numScores)
{
    float total = 0; //Accumulator
    float avg;  //Average
 
    for(int i = 0; i < numScores; i++)
    {
         total += gd[student].tests[i];
    }
    //Compute the average
    avg = total / numScores;
    //Assign to member named average
    gd[student].average = avg;            
}

//*****************************************************************
//Definition for function getGrade                                *
//This function will assign a letter grade to the grade member of *
//the GradeInfo struct pointer
//*****************************************************************
void getLetterGrade(GradeInfo *gd, int student)
{
    char grade;
    float avg = gd[student].average;
 
    if(avg >= 91 && avg <= 100)
        grade = 'A';
    if(avg >= 81 && avg <= 90)
        grade = 'B';
    if(avg >= 71 && avg <= 80)
        grade = 'C';
    if(avg >= 61 && avg <= 70)
        grade = 'D';
    if(avg < 60)
        grade = 'F';
        
    gd[student].grade = grade;        
}

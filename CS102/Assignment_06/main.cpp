//CS_102 Begining Programming C++
//Assignment: #6 Grade Book
//Programmer: Frank Mock
//Program Description: This program calculates students test scores and
//assigns a letter grade. Both the average score and letter grade is
//displayed for each student

#include<iostream>
#include<iomanip>
using namespace std;
    
    //Global Constants
    const int NUM_STUDENTS = 5;
    const int NUM_TESTS = 4;
    const int MAX_NAME_SIZE = 12;
    
    //Function prototypes
    void getStudentNames(char array[][MAX_NAME_SIZE], int);
    void getStudentGrades(double array[], int);
    double getAverageScore(double array[], int);
    char getLetterGrade(int, double);

int main()
{
    //Variables and arrays
    int count = 0;
    double averageScore = 0;
    char student_names[NUM_STUDENTS][MAX_NAME_SIZE];
    char letter_grades[NUM_STUDENTS];
    char grade;
    double student_01_scores[NUM_TESTS];
    double student_02_scores[NUM_TESTS];
    double student_03_scores[NUM_TESTS];
    double student_04_scores[NUM_TESTS];
    double student_05_scores[NUM_TESTS];
    
    cout << "Welcome to 'Grade Book' program\n";
    cout << "*******************************\n";
    getStudentNames(student_names, NUM_STUDENTS);
    
    do
    {
        cout << "\nEnter test scores for " << student_names[count] << endl;
        getStudentGrades(student_01_scores, NUM_TESTS);
        averageScore = getAverageScore(student_01_scores, NUM_TESTS);
        grade = getLetterGrade(count, averageScore);
        letter_grades[count] = grade; //Add student grade to array
        cout << "Letter grade is: " << letter_grades[count] << endl;
        count++;
        
        cout << "\nEnter test scores for " << student_names[count] << endl;
        getStudentGrades(student_02_scores, NUM_TESTS);
        averageScore = getAverageScore(student_02_scores, NUM_TESTS);
        grade = getLetterGrade(count, averageScore);
        letter_grades[count] = grade; //Add student grade to array
        cout << "Letter grade is: " << letter_grades[count] << endl;
        count++;
        
        cout << "\nEnter test scores for " << student_names[count] << endl;
        getStudentGrades(student_03_scores, NUM_TESTS);
        averageScore = getAverageScore(student_03_scores, NUM_TESTS);
        grade = getLetterGrade(count, averageScore);
        letter_grades[count] = grade; //Add student grade to array
        cout << "Letter grade is: " << letter_grades[count] << endl;
        count++;
        
        cout << "\nEnter test scores for " << student_names[count] << endl;
        getStudentGrades(student_04_scores, NUM_TESTS);
        averageScore = getAverageScore(student_04_scores, NUM_TESTS);
        grade = getLetterGrade(count, averageScore);
        letter_grades[count] = grade; //Add student grade to array
        cout << "Letter grade is: " << letter_grades[count] << endl;
        count++;
        
        cout << "\nEnter test scores for " << student_names[count] << endl;
        getStudentGrades(student_05_scores, NUM_TESTS);
        averageScore = getAverageScore(student_05_scores, NUM_TESTS);
        grade = getLetterGrade(count, averageScore);
        letter_grades[count] = grade; //Add student grade to array
        cout << "Letter grade is: " << letter_grades[count] << endl;
        count++; 
    }while(count < NUM_STUDENTS);
    
    system("pause");
    return 0;
}

//******************************************************
//Function definition for getStudentNames              *
//This function gets the names from the user and stores*
//them in a two dimensional char array                 *
//******************************************************
void getStudentNames(char nameArray[][MAX_NAME_SIZE], int rows)
{    
    for(int i = 0; i < rows; i++)
    {
         cout << "Enter student last name: ";
         cin >> nameArray[i];
    }
}

//*****************************************************
//Function definition for getStudentGrades            *
//This function gets the test grade numbers for each  *
//student and fills the associated array of scores    *                                    
//*****************************************************
void getStudentGrades(double scoresArray[], int test_count)
{
    for(int i = 0; i < test_count; i++)
    {
        int score = 0;
        do
        {
        cout << "Enter score for test #" << i +1 << ": ";
        cin >> score;
        if(score < 0 || score > 100)
        {
            cout << "Please enter a score above zero and below 100\n"; 
        }
        else
        {
            scoresArray[i] = score;
        }
        }while(score < 0 || score > 100);
    }
}

//*****************************************************
//Function definition for getAverageScore             *
//This function calculates the average score when     *
// given an array of scores. It returns a double      *  
// representing the score.                            *                          
//*****************************************************
double getAverageScore(double scoresArray[], int test_count)
{
 
    double total = 0;
    double average = 0;
    //Get a total of all the students scores
    for(int i = 0; i < test_count; i++)
    {
        total += scoresArray[i];
    }
        //Calculate an average score
        average = total / (test_count * 100);
        cout << fixed << showpoint << setprecision(2);
        cout << "Average score is: " << average << endl;
        return average;    
}

//*************************************************************
//Function definition for getLetterGrade                      *
//This function determines the letter grade when given an     *
//average score. This function will return a char representing*
//the letter grade.                                           *
//*************************************************************
char getLetterGrade(int student_number, double average)
{
    char letter_grade;
 
    if(average >= .90)
    {
        letter_grade = 'A';
        return letter_grade; 
    }
    else if(average >= .80 && average < .90)
    {
        letter_grade = 'B';
        return letter_grade; 
    }
    else if(average >= .70 && average < .80)
    {
        letter_grade = 'C';
        return letter_grade; 
    }
    else if(average >= .60 && average < .70)
    {
        letter_grade = 'D';
        return letter_grade;
    }
    else letter_grade = 'F';
         return letter_grade;
}
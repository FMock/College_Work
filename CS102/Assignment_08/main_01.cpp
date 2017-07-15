//CS_102 Begining Programming C++
//Assignment #8 Movie Statistics
//Programmer: Frank Mock
//Program Description: This program will collect statistical data from students
//about the number of movies they watch in a month. The program will output
//the average, median and mode.

#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
   //Define variables
   int numStudents, *numMoviesPtr, *dupArray, count, mode;
   double averageNumMovies, medianNumMovies;
 
   //Function prototypes
   int getMode(int *, int);
   void selectionSort(int *, int);
   double getAverage(const int *, int);
   double getMedian(int *, int);
   
   //Welcome user to program
   cout << "Welcome to the Movie Statistics program\n";
   cout << "---------------------------------------\n";
   
   do
   {
   //Ask user how many students were surveyed
   cout << "How many students were surveyed?: ";
   cin >> numStudents;
   }while(numStudents < 0);
   
   //Dynamically allocate an array of the number of students surveyed
   numMoviesPtr = new int[numStudents];
 
   //Enter the number of movies each student saw into the array
   for(count = 0; count < numStudents; count++)
   {
       cout << "\nEnter the number of movies student #" << count +1 << " saw ";
       cin >> numMoviesPtr[count]; 
   }
   
   //Display survey array results
   cout << "\nSurvey Results" << endl;
   cout << "----------------" << endl;
   for(count = 0; count < numStudents; count++)
   {
       cout << "Student #" << count + 1 << ": " << numMoviesPtr[count] << endl; 
   }
   
   //Sort the array of integers
   selectionSort(numMoviesPtr, numStudents);
   
   //Get the mode
   mode = getMode(numMoviesPtr, numStudents);
   if(mode == -1)
   {
      cout << "\nThere is no mode in the student survey array\n"; 
   }
   else
   {
      cout << "\nThe mode is: " << mode << endl;
   }

   //format decimal output
   cout << setprecision(3);
   //Get the average number of movies watched
   averageNumMovies = getAverage(numMoviesPtr, numStudents);
   cout << "The average number of movies watched: " << averageNumMovies << endl;
 
   //Get the median number of movies watched
   medianNumMovies = getMedian(numMoviesPtr, numStudents);
   cout << "The median number of movies is: " << medianNumMovies << endl;

   system("pause");
   return 0;
}

//**********************************************************
//Definition of function getMode                           *
//This function will determine the mode of an array of     *
//integers. It will return -1 if there is no mode.         *
//**********************************************************
int getMode(int *arr, int size)
{
    int num = 0,
        count = 0,
        max = 0,
        mode = 0;

    //Search for mode
    for(int index = 0; index < size; index++)
    {
        if(num != arr[index])
        {
            num = arr[index];
            count = 1;
        }
        else
        {
            count++;
        }
        
        if(count > max)
        {
            max = count;
            mode = num;
        }
    }

    if(max == 1) //if no mode
    {   
        max = -1;
        return max; //return -1
    }
    else
    {
        return mode;
    }
}

//********************************************************
//Definition of function selectionSort                   *
//This function performs an ascending order selection    *
//sort on an integer array. size is the number of        *
//elements                                               *
//********************************************************
void selectionSort(int *arr, int size)
{
    int startScan, minIndex, minValue;
    
    for(startScan = 0; startScan < (size - 1); startScan++)
    {
        minIndex = startScan;
        minValue = arr[startScan];
        for(int index = startScan + 1; index < size; index++)
        {
            if(arr[index] < minValue)
            {
                minValue = arr[index];
                minIndex = index; 
            } 
        }
        arr[minIndex] = arr[startScan];
        arr[startScan] = minValue; 
    } 
}

//**********************************************************
//Definition for function getAverage                       *
//This function will return the average of an array of     *
//integers. size is the number of elements                 *
//**********************************************************
double getAverage(const int *arr, int size)
{
     int total;
     double average;
 
    for(int index = 0; index < size; index++)
    {
        total += arr[index];
    }
    
    //calculate average
    average = total / static_cast<double>(size);
    return average; 
}

//***********************************************************
//Definition for function getMedian                         *
//This function returns the median of an array of numbers   *
//size is the number of elements                            *
//***********************************************************
double getMedian(int *arr, int size)
{
    int middleNumOne, middleNumTwo, middle;
    double median;
    
    if(size % 2 == 0) //If size is an even number
    {
        middleNumOne = (size / 2) - 1;
        middleNumTwo = middleNumOne + 1;
        median = (arr[middleNumOne] + arr[middleNumTwo]) / static_cast<double>(2);
        return median; 
    }
    else //size is an odd number
    {
        middle = (size / 2) + 1;
        median = static_cast<double>(middle);
        return median; 
    }
}

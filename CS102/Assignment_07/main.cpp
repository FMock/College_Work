//CS_102 Begining Programming C++
//Assignment: #7 Binary String Search
//Programmer: Frank Mock
//Program Description: This program will sort an array of char strings and 
//then allow a user to search the array for a name. The program will perform
//a binary search

#include<iostream>
#include<string>

using namespace std;

//Global constants
const int NUM_NAMES = 20, SIZE = 17;

//Function prototypes
void sortStringArray(char [][SIZE], int);
int binarySearch(char [][SIZE], int, char [][SIZE]);

int main()
{   

    char names[NUM_NAMES][SIZE] = {"Zollins, Bill", "Smith, Bart", "Allen, Jim",
                                   "Griffin, Jim", "Stamey, Marty", "Rose, Geri",
                                   "Taylor, Terri", "Johnson, Jill",
                                   "Allison, Jeff", "Looney, Joe", "Wolfe, Bill",
                                   "James, Jean", "Weaver, Jim", "Pore, Bob",
                                   "Rutherford, Greg", "Javens, Renee",
                                   "Harrison, Rose", "Setzer, Cathy",
                                   "Pike, Gordon", "Holland, Beth"};
                                   
    char userInput[1][SIZE];//To hold user input to search for
    char choice = 'y';
    int position;
                                   
    //Call function sortStringArray to alphabetically sort string array                               
    sortStringArray(names, NUM_NAMES);
    //Welcome the user
    cout << "Welcome to the Binary String Search" << endl;
    cout << "-----------------------------------\n" << endl;
    cout << "This program will search an array of names and return the\n";
    cout << "position in the array." << endl;
    do
    {
        //Ask user to enter name to search for
        cout << "\nEnter the name to search for: ";
        //Get input from user and assign to userInput char string array
        cin.getline(userInput[0], SIZE);
        //Search names array for input entered by user 
        position = binarySearch(names, NUM_NAMES, userInput);
        if(position > -1)//If found in array
            cout << "\nFound " << userInput[0] << " at position " << position << endl;
        else
            cout << "\nDid not find name in array" << endl;
        //Ask user if they want to perform another search
        cout << "\nWould you like to search for another name? (y/n): ";
        cin >> choice;
        cin.ignore();
    }while(choice == 'y');
    
    cout << "\nNow displaying the sorted array\n";
                                       
    //Display sorted array of names
    for(int j = 0; j < NUM_NAMES; j++)
        cout << names[j] << endl;
    
    system("pause");
    return 0;
}

//****************************************************
//Function definition for sortStringArray            *
//This function will alphabetically sort an array of *
//strings. size is the number of elements in the     *
//array.                                             *
//****************************************************
void sortStringArray(char stringArray[][SIZE], int size)
{
    bool swap;
    char temp[1][SIZE];
    do
    {   
        swap = false;
        for(int count = 0; count < (size - 1); count++ )
        {
            if(strcmp(stringArray[count],stringArray[count + 1]) > 0)
            {
                strcpy(temp[0],stringArray[count]);
                strcpy(stringArray[count],stringArray[count + 1]);
                strcpy(stringArray[count + 1], temp[0]);
                swap = true;
            }
        }
    }while(swap); 
}

//****************************************************************
//Function definition for binarySearch. This function will search*
//a char string array for a user inputed string and returns the  *
//subscript position number                                      *                          
//****************************************************************
int binarySearch(char array[][SIZE], int numElements, char value[][SIZE])
{
     int first = 0,
         last = numElements - 1,
         middle,
         position = - 1;

     bool found = false;

    while(!found && first <= last)
    {
        middle = (first + last) / 2; //calculate mid point

        if(strcmp(array[middle], value[0]) == 0) //If value is found at middle
        {
            found = true;
	           position = middle;
        }
        else if(strcmp(array[middle], value[0]) > 0) //If value is in lower half
        {
            last = middle - 1;
        }
        else
        {
            first = middle + 1; //If value is in upper half
        }
    }
    return position;  
}

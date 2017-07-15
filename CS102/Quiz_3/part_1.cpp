//CS_102 Begining Programming C++
//Assignment: Quiz 3 part 1 
//Programmer: Frank Mock
//Program Description: Part 1 of Quiz 3. This program will open the file
//data.txt for both input and output but first determines if the file exists.
//If the file does not exist, the program will create it and open it for input
//and output.

#include<iostream>
#include<fstream> //Must include this preprocessor directive to use fstream
using namespace std;

int main()
{

    const int SIZE = 200;
    char input[SIZE];
    
    //Create input file stream object
    ifstream inFile("data.txt", ios::in);
    ofstream outFile("data.txt", ios::out|ios::app);
    
    //NOTE TO INSTRUCTOR
    //fstream dataFile("data.txt", ios::in | ios::out);
    //This line did not allow me to read and write so I
    //used seperate file stream objects 

    //Could not open data.txt
    if(!inFile)
    {
        cout << "data.txt did not exist\n";
        cout << "and had to be created\n";
     
        //Write to file
        cout << "Writing to file\n";
        outFile << "Test text on file\n";       
    }
    else
    {

        //File data.txt already exist
        cout << "Writing to file\n";
        outFile << "Test text on file\n";
        //Reading text from file
        cout << "READING TEXT FROM FILE\n";
        cout <<"***********************\n";
        inFile.getline(input, SIZE);
        while(!inFile.eof())
        {
            cout << input << endl;
            inFile.getline(input, SIZE); 
        }

    }

    system("pause");
    return 0;
}

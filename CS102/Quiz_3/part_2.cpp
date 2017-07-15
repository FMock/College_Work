//CS_102 Begining Programming C++
//Assignment Part 2 of Quiz 3
//Programmer: Frank Mock
//Program Description: This program will calculate and display the size
//of a file called data.txt which is in the same directory as the program file

#include<iostream>
#include<fstream>
using namespace std;

int main()
{
    long begin, end;
    
    //Open file stream object  - pointer is at beginning of file
    ifstream DataFile("data.txt");
    //Assign to begin the value returned by member function tellg()
    begin = DataFile.tellg();
    //Move pointer to end of file    
    DataFile.seekg(0, ios::end);
    //Assign to end the value returned by member function tellg()
    end = DataFile.tellg();
    //Calculte and display the number of bytes
    cout << "The file size is " << (end - begin) << " bytes.\n" << endl;
    
    system("pause");
    return 0;
}

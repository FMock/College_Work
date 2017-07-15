//CS_102 Begining Programming C++
//Assignment Part 3 of Quiz 3
//Programmer: Frank Mock
//Program Description: This program will rewind the file stream object
//named infoFile after the file has read to the end of the file

#include<iostream>
#include<fstream>
using namespace std;

int main()
{
    const int SIZE = 200;
    char data[SIZE];
    
    fstream infoFile("data.txt");
    
    infoFile.getline(data, SIZE);
    while(!infoFile.eof())
    {
        cout << data << endl;
        infoFile.getline(data, SIZE); 
    }
    
    //Rewind to the begining of the file
    infoFile.seekg(0, ios::beg);
    
    //Close file stream
    infoFile.close();
    
    system("pause");
    return 0;
}

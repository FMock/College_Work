//CS_102 Begining Programming C++
//Quiz #1 - Bitset
//Programmer: Frank Mock
//Program Description

#include<iostream>
#include<bitset> //This must be included to use bitset
using namespace std;

int main()
{
 //Create a bitset with 8 elements
 bitset<8> bs = ((long) 9); //Nine is coverted to binary and inserted in bitset
 
 cout << bs << endl;// Display the contents of bitset (Binary number 9)
 
    system("pause");
    return 0;
}

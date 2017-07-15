//CS_102 Begining Programming C++
//Assignment: #4  Hotel Ocuupancy
//Programmer: Frank Mock
//Program Description: Programm will calculate the occupancy rate for a hotel

#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
    int floors, rooms, occupied, unoccupied;
    int totalRooms = 0;
    int totalOccupied = 0;
    double percentOccupied = 0.0;
    
    cout << "Welcome to the Hotel Occupancy program\n";
    cout << "--------------------------------------\n";
    
    //Get the number of floors from user
    do
    {
        cout << "How many floors does the hotel have? ";
        cin >> floors;
    }while(floors < 1);
    
    //Iterate through each floor - skip #13
    for(int i = 1; i <= floors; i++)
    {
         if(i == 13)//Skip floor #13
             continue;

         do
         {
             cout << "How many rooms are on floor " << i << ": ";
             cin >> rooms;                   
         }while(rooms < 10);//Do not allow less than ten rooms
         
         do
         {
         cout << "How many are occupied? ";
         cin >> occupied;
         }while(occupied > rooms);//Ensure occupied does not exceed rooms
         
         //Keep totals
         totalRooms += rooms;
         totalOccupied += occupied;   
    }
    
    //Calculate the total unoccupied rooms
    unoccupied = totalRooms - totalOccupied;
    //Calculate the percent occupied
    percentOccupied = totalOccupied / static_cast<double>(totalRooms);
    
    //Display the results
    cout << "\nThere a total of " << totalRooms << " rooms" << endl;
    cout << "Total rooms occupied are " << totalOccupied << endl;
    cout << "The total rooms unoccupied are " << unoccupied << endl;
    cout << fixed << showpoint << setprecision(2);
    cout << "The percent occupied is " << percentOccupied << endl;
     
    system("pause");
    return 0;
}

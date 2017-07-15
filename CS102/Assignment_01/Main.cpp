//CS_102_01 Intro C++
//Assignment #1
//Frank Mock 
//06-29-2010
//This program calculates and displays the number of miles a car can drive
//in town and in the city given the average miles per gallon for each and
//the fuel tank capacity.

#include<iostream>
using namespace std;

int main()
{
//Initialize variables
 double distanceTown, distanceHighway;
 double city_mpg = 21.5, highway_mpg = 26.8;
 const double GAS_TANK_SIZE = 20;
 double userFuelTank;
 char response = 'y';
 
 //Calculate example total distances based on sample MPG
 distanceHighway = GAS_TANK_SIZE * highway_mpg;
 distanceTown = GAS_TANK_SIZE * city_mpg;
 
 //Welcome user to the program
 cout << "Welcome to the Vehicle Distance Calculator\n\n";
 
 //Display Sample data
 cout << "Sample Vehicle Fuel Economy Data\n";
 cout << "***********************************\n";
 cout << "City MPG: 21.5\n";
 cout << "Highway MPG: 26.8\n\n";
 cout << "       Fuel Tank Capacity\n";
 cout << "************************************\n";
 cout << "Total Fuel: 20 Gallons\n\n";
 cout << "       Total Miles Per Tank\n";
 cout << "************************************\n";
 cout << "Highway: "<< distanceHighway << "\n";
 cout << "City: " << distanceTown << "\n\n";
 
 //Continue until the user does not answer 'y'
 while(response == 'y')
 { 
      //collect input from user
      cout << "Enter your car's city MPG\n";
      cin >> city_mpg;
      cout << "Enter your car's highway MPG\n";
      cin >> highway_mpg;
      cout << "How many total gallons does the fuel tank hold?\n";
      cin >> userFuelTank;
      
      //Calculate distances based on user input
      distanceHighway =  userFuelTank * highway_mpg;
      distanceTown = userFuelTank * city_mpg;
      
      //Display data to user
      cout << "\nYour Vehicle Fuel Economy Data\n";
      cout << "***********************************\n";
      cout << "City MPG: " << city_mpg << "\n";
      cout << "Highway MPG: "<< highway_mpg <<"\n\n";
      cout << "       Fuel Tank Capacity\n";
      cout << "************************************\n";
      cout << "Total Fuel: "<< userFuelTank <<" Gallons\n\n";
      cout << "       Total Miles Per Tank\n";
      cout << "************************************\n";
      cout << "Highway: "<< distanceHighway << "\n";
      cout << "City: " << distanceTown << "\n\n";
 
      //Ask the user if he/she would like to calculate another
      cout << "Would you like to calculate another? (y/n)\n";
      cin >> response;            
 }
 
 //Say goodbye before the program ends
 cout << "Good Bye!\n\n";
 system("pause");
 return 0;    
}

//Class: CS102_01 C++
//Programmer: Frank Mock
//Date: 07-04-2010
//Assignment #2
//This program will display a sales tax report based on sales
//input data entered by a user

#include<iostream>
#include<iomanip> 
using namespace std;

int main()
{
   //initialize variables
   const double STATE_SALES_TAX = .04;
   const double COUNTY_SALES_TAX = .02;
   double totalCollected, totalSalesTax, totalCountyTax, totalStateTax, totalSales; 
   char month[12];
   char response = 'y';
   int year;
   
   //Welcome user to the program 
   cout << "Welcome to the Monthly Sales Tax program\n\n";
   
   //Continue program loop while user response is 'y'
   while(response == 'y')
   {
      cout << "\nEnter monthly sales info to generate a report\n";
      cout << "---------------------------------------------\n";
      cout << "Enter the month: ";
      cin >> month;
      cout << "Enter the year: ";
      cin >> year;
      cout << "Enter total amount collected including sales tax: ";
      cin >> totalCollected;
      
      //Calculate the total sales
      totalSales = totalCollected / (STATE_SALES_TAX + COUNTY_SALES_TAX + 1);
      //Calculate the total sales tax
      totalSalesTax = totalCollected - totalSales;
      //Calculate total state tax
      totalStateTax = totalSales * STATE_SALES_TAX;
      //Calculate total county tax
      totalCountyTax = totalSales * COUNTY_SALES_TAX;
      
      //Display the report
      cout << "\nMonth of " << month << " " << year <<"\n";
      cout << "-------------------------------------------\n";
      cout << setprecision(2) << fixed;
      cout << "Total Collected: " << setw(8)<< totalCollected << "\n";
      cout << "Total Sales: " << setw(12)<< totalSales << "\n";
      cout << "County Tax: " << setw(13)<< totalCountyTax << "\n";
      cout << "State Tax: " << setw(14)<< totalStateTax << "\n";
      cout << "Total Tax: " << setw(14)<< totalSalesTax << "\n";           
      cout << "\nWould you like to continue? (y/n) ";
      cin >> response;               
   }
   cout << "Thank you and goodbye!\n\n";
   system("pause");    
   return 0;
}

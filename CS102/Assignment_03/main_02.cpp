//CS_102_Begining C++
//Assignment #3 part 2 using Switch / Case - Long Distance Calss
//Frank Mock
//07-06-2010
//This program asks for the starting time and the number
//of minutes of the call and calculates and displays the
//charges.

#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
    double startTime, 
           numberOfMinutes,
           fractionalTime,
           currentCharges;
    const double RATE_A = 0.12;
    const double RATE_B = 0.55;
    const double RATE_C = 0.35;

    bool startTimeOk = false;
    bool callDurationOk = false;
    
    char response = 'y';
    char rateCode;
    
    cout << "Welcome to the Phone Charges program\n";
    cout << "--------------------------------------\n";
    cout << "To determine the phone charges, enter the call starting time and the number of\n"; 
    cout << "minutes of the call.\n\n";
    cout << "Enter the call starting time as a floating point number in the form of HH.MM\n\n";
    cout << "Example: 07:30 pm would be 19.30\n";
    cout << "Example: five minutes past midnight is 00.05\n\n";
    
    while(response == 'y' || response == 'Y')
    {
        cout << "Enter phone call starting time: ";
        cin >> startTime;
        cout << "Enter call duration in minutes: ";
        cin >> numberOfMinutes;
    
        while(startTimeOk == false)
        {
            //Determine if the minutes entered is correct
            fractionalTime = startTime - static_cast<int>(startTime);
            if(fractionalTime >= 0.0 && fractionalTime <= 0.59)
            {
                 //Determine if the time entered is correct
                 if(startTime >= 0 && startTime <= 23.59)
                 {
                     startTimeOk = true;
                 }
                 else
                 {
                     //The call start time was entered incorrectly
                     cout << "The call start time was entered incorrectly\n";
                     cout << "Please enter call start time: ";
                     cin >> startTime;   
                 }
            }
            else
            {
                //The minutes were entered incorrectly
                cout << "The call start time minutes were entered incorrectly\n";
                cout << "Please enter call start time: ";
                cin >> startTime;
            }
        }

       
        //Check that the call duration is a positive number and it is below 10,000
        while(callDurationOk == false)
        {
             if(numberOfMinutes > 0 && numberOfMinutes < 10000)
             {
                  callDurationOk = true; 
             }
             else
             {
                  //The call duration entered is invalid
                  cout << "The call duration entered is invalid\n";
                  cout << "Please enter the call duration: ";
                  cin >> numberOfMinutes; 
             } 
        }
    

            //Determine the rate code based on the start time
            if(startTime >= 0 && startTime <= 6.59)
            {
                rateCode = 'A'; 
            }
            else if(startTime >= 7.0 && startTime <= 19.0 )
            {
                rateCode = 'B';  
            }
            else
            {
                rateCode = 'C';
            }
    //Determine the current charges
    switch(rateCode)
    {
        case 'A': currentCharges = numberOfMinutes * RATE_A; 
                  cout << "\nThe charges for this call are: " << currentCharges << "\n";
                  break;

        case 'B': currentCharges = numberOfMinutes * RATE_B; 
                  cout << "\nThe charges for this call are: " << currentCharges << "\n";
                  break;
                  
        case 'C': currentCharges = numberOfMinutes * RATE_C; 
                  cout << "\nThe charges for this call are: " << currentCharges << "\n";
                  break; 
    }

            //reset flags
            startTimeOk = false;
            callDurationOk = false;
        
            //Ask the user if they would like to continue
            cout << "\nWould you like to get the charges for another call? (y/n) ";
            cin >> response;
    }
    
    cout << "Goob bye!\n";
    
    system("pause");
    return 0;    
}

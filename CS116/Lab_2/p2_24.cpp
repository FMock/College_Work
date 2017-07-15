

#include "ccc_win.h"

int ccc_win_main()
{
        
                cwin << Message(Point(-5, -4), "Frank Mock");
                cwin << Message(Point(-5, -5), "Lab 2.24");
                cwin << Message(Point(-5, -6), "Graph Values Entered by User");
        
        
                //This prompt is not important and may not display on some machines
                string not_used = cwin.get_string("Ready To Begin?(Y or N");
                //Define variables
                int measurement;
                int measurments[4];
                string names[4];
                //set up coordinate system to be used
                int highest = cwin.get_int("What is the highest value of the data set?");
                cwin.coord(-10, 5, highest + 10, -10);
        
                
                //Get Name and Number input from user
                for(int count = 0; count <= 3; count++)
                {
                        string name = cwin.get_string("Please type name");
                        names[count] = name;
                        do
                        {
                        measurement = cwin.get_int("Enter measurement:");
                        measurments[count] = measurement;
                        }while(measurement > highest);
                }
        
                
                for(int count = 0; count <=3; count++)
                {
                        string n = names[count];
                        int m = measurments[count];
                        Point topleft(0, count);
                        Point topright(m, count);
                        Point bottomleft(0, count - .5);
                        Line horizontal(topleft, topright);
                        Line vertical(topleft, bottomleft);
                        cwin << horizontal << vertical;
                        cwin << Message(Point(0, count), n);
                        horizontal.move(0, - .5);
                        vertical.move(m, 0);
                        cwin << horizontal << vertical;
                }
        
        return 0;
}

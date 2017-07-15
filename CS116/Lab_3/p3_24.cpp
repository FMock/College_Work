

#include "ccc_win.h"

int ccc_win_main()//authors entry point that calls name
{

//draw a 1x1 unit square
Point top_left(0, 1);
Point top_right(1, 1);
Point bottom_left(0, 0);
        
Line horizontal(top_left, top_right);
Line vertical(top_left, bottom_left);
        
cwin << horizontal << vertical;
        
horizontal.move(0, -1);
vertical.move(1, 0);
        
cwin << horizontal << vertical;


Point p = cwin.get_mouse("Try to click inside the square.");


//assign x and y coordinates to double variable
double x = p.get_x();
double y = p.get_y();
//determine if the user clciked inside the square
if(x <= 1 && x >= 0 && y <=1 && y >= 0)
{
 cwin << p << Message(p, "Congratulations, You did it!");
}
else
{
 cwin << p << Message(p, "Sorry, You missed!");
}

return 0;
}

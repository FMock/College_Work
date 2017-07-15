#include "ccc_win.h"

int ccc_win_main()
{
	
	//Draw Square
	Point top_left(1, 3);
	Point top_right(1, 4);
	Point bottom_left(2, 3);
	
	Line horizontal(top_left, top_right);
	Line vertical(top_left, bottom_left);
	
	cwin << horizontal << vertical;
	
	horizontal.move(1, 0);
	vertical.move(0, 1);
	
	cwin << horizontal << vertical;

	//Capture the x and y coordinate where the user clicks
   string name = cwin.get_string("Please type your name:");
   Circle c(Point(0, 0), 1);
   cwin << c;
   Point m = cwin.get_mouse("Please click inside the circle.");
   cwin << m << Message(m, name + ", you clicked here");

   return 0;
}

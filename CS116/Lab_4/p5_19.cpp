
#include"cannonball.h"

#include "ccc_win.h"

int ccc_win_main()
{
 Cannonball c(10, 20);
 double angle = cwin.get_double("Enter the launch angle in degrees: ");
 double velocity = cwin.get_double("Enter the initial velocity in m/s:");
 c.shoot(angle,velocity);
 cwin << Message(Point(0,0),"Test");
return 0;
}

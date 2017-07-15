
#include"cannonball.h"
Cannonball::Cannonball(double w, double x)
{
 x_position = x;
 y_position = 0;
 x_velocity = 0;
 y_velocity = 0;
}
void Cannonball::move(double s)
{
  x_position++;
}
/**
Use the Point class from the authors graphic library 
to indicate the positions that the cannonball
is in as it moves through its trajectory.
*/
void Cannonball::plot() const
{
 
}
void Cannonball::shoot(double a, double v)
{
  do
  {
    move(0.1);
  }while(x_position < 50);
}

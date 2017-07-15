
#include"ccc_win.h"
#include<cmath>
const double g = -9.81; //m/sec x sec
const double pi = 4 * atan(1.0);
class Cannonball
{
private:
  double x_position;
  double y_position;
  double x_velocity;
  double y_velocity;
public:
  Cannonball(double w, double x);
  void move(double s);
  void plot() const;
  void shoot(double a, double v);
};

\documentclass{article}
\usepackage{graphicx, color}
\usepackage{hyperref}
\usepackage{tikz}
\usepackage{pgf-umlcd}
\title{\color{blue}P5.19}
\author{\color{blue}Frank Mock}
\date{\color{blue}October 10, 2011}
\begin{document}
\maketitle
\section{Specification}
	Design a class Cannonball to model a cannonball that is fired into the air. 
    A ball has an x and a y position and an x and y velocity
		
	Supply the following member functions:
		\begin{itemize}
		\item	A constructor with a weight and an x-position (the y-position is initially 0)
		\item	A member function move(double sec) that moves the ball to the next position (First compute 
                the distance traveled in sec seconds, using the current velocities, then update the x- and y-positions; 
                then update the y-velocity by taking into account the gravitational acceleration of - 9.81 m/sec2; the 
                x-velocity is unchanged.)
		\item	A member function plot that plots the current location of the cannonball
		\item	A member function shoot whose parameters are the angle a and initial velocity v 
                (Compute the x-velocity as v cos a and the y-velocity as v sin a; then keep calling move with a time 
                interval of 0.1 seconds until the y-position is 0; call plot after every move.)
		\end{itemize}
		
	Use this class in a program that prompts the user for the starting angle and the initial velocity. Then call shoot.

\section{Design}
	\begin{tikzpicture}
	\begin{class}[text width=8cm]{Cannonball}{0,0}
	\attribute {- x\_position : double}
	\attribute {- y\_position : double}
	\attribute {- x\_velocity : double}
	\attribute {- y\_velocity : double}
	\operation {+ Cannonball ( weight : double, x\_pos : double) }
	\operation {+ move ( second : double ) : void }
	\operation {+ plot () : void }
	\operation {+ shoot ( angle : double, velocity : double ) : void }
	\end{class}
	\begin{class}{GraphicWindow}{8,0}
	\end{class}
	\begin{class}{Point}{8,-2}
	\end{class}
	\association{Cannonball}{}{1} {GraphicWindow}{}{1}
	\association{Cannonball}{}{1} {Point}{}{0..*}
	\end{tikzpicture}
The velocity can be split into x and y components using these formulas from trigonometery

\begin{tikzpicture}
\draw(0,0)rectangle(4,8);
\draw(3.5,0)rectangle(4,0.5);
\draw(0.5,0.5)node[]{$\alpha$};
\draw(2,-0.5)node[]{$v \times \cos \alpha$};
\draw(5,4)node[]{$v \times \sin \alpha$};
\draw[->] (0,0) -- (4,8);
\end{tikzpicture}\\


\section{Implementation}
g is the gravitational acceleration of $-9.81 \frac{m}{sec*2}$.
a good approximation of $\pi$ is $ 4 \times \arctan 1.0$ Which we will
need to convert from the angle in degrees to the angle in radians.
The c++ sin and cos functions expect the argument to be in radians.
@o cannonball.h
@{
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
@}
Assume the initial y position is always zero (starting from the ground)
Weight does not seem to affect the trijectory, but we store it for possible later
use. Use the Point class from the authors graphic library to indicate the positions
that the cannonball is in as it moves through its trajectory.
@o cannonball.cpp
@{
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
@}
In the main program, we create a cannonball, get initial angle and velocity from user
then call shoot
@o p5_19.cpp
@{
#include"cannonball.h"
@<Include Files@>
int ccc_win_main()
{
 Cannonball c(10, 20);
 double angle = cwin.get_double("Enter the launch angle in degrees: ");
 double velocity = cwin.get_double("Enter the initial velocity in m/s:");
 c.shoot(angle,velocity);
 cwin << Message(Point(0,0),"Test");
return 0;
}
@}

@d Include Files
@{
#include "ccc_win.h"
@}

@o p5_19.bat
@{
g++ -mwindows -I C:\C++_Programs\CS-116\cannonball\cccfiles -o p5_19 p5_19.cpp cannonball.cpp ^
C:\C++_Programs\CS-116\cannonball\cccfiles\ccc_msw.cpp ^
C:\C++_Programs\CS-116\cannonball\cccfiles\ccc_shap.cpp ^
-lgdi32
@}

\end{document}

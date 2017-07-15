\documentclass{article}
\usepackage{graphicx}
\usepackage{hyperref}
\usepackage{tikz}
\title{P3.24}
\author{Frank Mock}
\begin{document}
\maketitle
\section{Specification}
Exercise P3.24.      
Write a program that draws a square with corner points (0, 0) and (1, 1). 
Prompt the user for a mouse click. If the user clicked inside the square, 
then show a message Congratulations. Otherwise, show a message You missed. 
\section{Design}
Assume that the points forming the square have dimensions:\\
\begin{tikzpicture}
\draw(0,0) rectangle(1,1);
\draw(0,0) node[anchor=east]{(0,0)};
\end{tikzpicture}\\
and that the user's point is in variable $p$.
Display the message to the user someplace outside the square. For
example at some point (2,2).
\section{Implementation}

@o p3_24.cpp
@{
@<Include Files@>
int ccc_win_main()//authors entry point that calls name
{
@<Draw a Square@>
@<Get the point where the user clicked@>
@<Determine if that point is in the square@>
return 0;
}
@}
The authors graphics library includes a \verb|Point| class and
a \verb|Line| class which allow points and lines to be drawn on
the screen. A \verb|Point| has an \verb|x-| and a \verb|y-coordinate.|
For example, \verb|Point(1,3)| is a \verb|Point| with \verb|x-coordinate|
1 and \verb|y-coordinate| 3. Two points can be joined by a line, represented
by a \verb|Line| object that is contructed from two \verb|Point| objects,
it's start point and end points.\\
\indent \verb|Point p(1, 3);|\\
\indent \verb|Point q(4, 7);|\\
\indent \verb|Line s(p, q);|\\
Both the \verb|Point| and \verb|Line| class implement the member function
\verb|move(x, y)| which changes position of an object, moving the entire
object by the \verb|x| and \verb|y| units specified.\\
\indent \verb|s.move(1, 0)|\\
This moves the line \verb|s| 1 unit in the x direction (to the right). cwin
is a window object used to display graphic objects such as \verb|Line| and
\verb|Point| to the screen.\\
\indent \verb|cwin << s;|\\
@d Draw a Square
@{
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
@}

In the author's library, there is a function named \verb|get_mouse| that
returns the point where the left-button of the mouse was clicked. Invoke it
using the \verb|cwin| object. Store the point in variable \verb|p|
@d Get the point where the user clicked
@{
Point p = cwin.get_mouse("Try to click inside the square.");
@}

There is a member function namedverb|get_x()| and \verb|get_y()| to retrieve
the coordinates from a point object. (e.g. \verb|p|). Compare those coordinates
to the boundries of the square.
@d Determine if that point is in the square
@{
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
@}

@o p3_24.bat
@{
g++ -mwindows -I C:\C++_Programs\bigc2_sourcecode\cccfiles -o p3_24 p3_24.cpp ^
C:\C++_Programs\bigc2_sourcecode\cccfiles\ccc_msw.cpp ^
C:\C++_Programs\bigc2_sourcecode\cccfiles\ccc_shap.cpp ^
-lgdi32
@}

Theses are the include files for this program
@d Include Files
@{
#include "ccc_win.h"
@}

\section{Test}
\end{document}
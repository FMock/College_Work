\documentclass{article}
\usepackage{graphicx,color}
\begin{document}
\setlength{\parindent}{0in}
\title{\color{blue}Lab 2 Excercise P2.24}
\author{\color{blue}Frank Mock}
\date{\color{blue}September 18, 2011}
\maketitle
\section{Specification}

Exercise P2.24.
      
Make a bar chart to plot a data set of user intput.
Prompt the user to type in four names and measurements. 
Then display a bar graph. Make the bars horizontal for easier labeling.\\
\begin{tabular}{lc}
Name & Longest Span(ft) \\
Golden Gate & 4,200 \\
Brooklyn & 1,595 \\
Delaware Memorial & 2,150 \\
Mackinaw &3,800 
\end{tabular}
\section{Design}
\begin{enumeration}
\item Display message describing program
\item Define variables and setup the coordinate system. Prompt user for 
highest number in data set to assist setting up coordinate system
\item Prompt user to type four names and measurements and store in arrays
\item Display the bar graph
\end{enumeration}
\section{Analysis}
This exercise uses the authors graphics library ccc\_win.h available
from \footnote{www.wiley.com/college/horstmann}
To use this graphics library, you must include the header file ccc\_win.h 
into your program. Moreover, you need to supply the function ccc\_win\_main 
instead of main as the entry point to your program.
@d Display message describing program
@{
	cwin << Message(Point(-5, -4), "Frank Mock");
	cwin << Message(Point(-5, -5), "Lab 2.24");
	cwin << Message(Point(-5, -6), "Graph Values Entered by User");
@}
The first use of cwin is ignored on my machine but the machine I
used in class did not do this. To remedy this inconsistency, I prompt 
the user to see if they are ready. Their answer is not used. I choose
to create array data types to store user input. To make setting up
the coordinate system easier, I ask the user for the highest value
of the data set and use this in cwin's call to coord().
@d Define variables and setup the coordinate system
@{
	//This prompt is not important and may not display on some machines
	string not_used = cwin.get_string("Ready To Begin?(Y or N");
	//Define variables
	int measurement;
	int measurments[4];
	string names[4];
	//set up coordinate system to be used
	int highest = cwin.get_int("What is the highest value of the data set?");
	cwin.coord(-10, 5, highest + 10, -10);
@}
\\
\\
\\
I used a for loop to get the four names and measurements. The code
performs some validation utilizing a do-while loop and not allowing 
a number higher than what the user already inputed as the highest 
value of the data set. This ensures that the coordinate system will 
not be compromised by the values entered by the user. We can get 
information from the user using member functions from the GraphicWindow 
class. We can use get\_string for the name of the bridge and \verb|get_int| 
for it's length.
@d Prompt user for names and measurements and store in arrays
@{	
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
@}
I used a for-loop to interate through each array and draw the
users inputed data to the screen.
@d Draw bar graph info to screen
@{	
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
@}
@o p2_24.cpp
@{
@<include files@>
int ccc_win_main()
{
	@<Display message describing program@>
	@<Define variables and setup the coordinate system@>
	@<Prompt user for names and measurements and store in arrays@>
	@<Draw bar graph info to screen@>
	return 0;
}
@}
These are the include files needed for this program
@d include files
@{
#include "ccc_win.h"
@} 
\section{Image of program p2\_24.exe running}
\includegraphics[width=18cm]{p2_24.jpg}
\end{document}
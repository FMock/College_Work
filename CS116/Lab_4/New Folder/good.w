\documentclass{article}
\usepackage{graphicx}
\usepackage{hyperref}
\usepackage{tikz}
\usepackage{pgf-umlcd}
\title{P5.19}
\author{Dilraj Singh}
\begin{document}
\maketitle

\section{Specification}
	Design a class Cannonball to model a cannonball that is fired into the air. A ball has an x and a y position and an x and y velocity
		
	Supply the following member functions:
		\begin{itemize}
		\item	A constructor with a weight and an x-position (the y-position is initially 0)
		\item	A member function move(double sec) that moves the ball to the next position (First compute the distance traveled in sec seconds, using the current velocities, then update the x- and y-positions; then update the y-velocity by taking into account the gravitational acceleration of - 9.81 m/sec2; the x-velocity is unchanged.)
		\item	A member function plot that plots the current location of the cannonball
		\item	A member function shoot whose parameters are the angle a and initial velocity v (Compute the x-velocity as v cos a and the y-velocity as v sin a; then keep calling move with a time interval of 0.1 seconds until the x-position is 0; call plot after every move.)
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

\section{Implementation}
	
	@o cannonball.h
	@{
		class Cannonball
		{
			private:
				double x_position;
				double y_position;
				double x_velocity;
				double y_velocity;
			public:
				Cannonball( double w, double x );
				void move( double s);
				void plot() const;
				void shoot( double a, double v );
		};		
	@}

	@o cannonball.cpp
	@{
		#include "cannonball.h"
		Cannonball::Cannonball( double w, double x )
		{
		
		}
		void Cannonball::move( double s)
		{
		
		}
		void Cannonball::plot() const
		{
		
		}
		void Cannonball::shoot( double a, double v )
		{
		
		}
	@}
		
	@o p5_19.cpp
	@{
		#include "cannonball.h"
		#include <iostream>
		uaing namespace std;
		Cannonball c( 10,20 );
	@}
	
	@o p3_24.bat
	@{
		
	@}	

\end{document}
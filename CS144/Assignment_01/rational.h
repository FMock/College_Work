#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>
#include <cassert>

using namespace std;

class Rational{
public:
	/**
		Constructor covers zero, one or two arguments.
		@param n the numerator. Default is 0
		@param d the denominator. Default is 1.
	*/
	Rational();

	Rational(int n);

	Rational(int n, int d);

	Rational(double n);

	/**
		Returns the value of numerator
		@return the value of numerator
	*/
	int getNumerator() const;

	/**
		Returns the value of denominator
		@return the value of denominator
	*/
	int getDenominator() const;

	/**
		Sends the Rational to the standard output device (screen)
	*/
	void print() const;

	/*
		Uses the output stream object to print the rational
	*/
	void print(ostream&) const;
	
	/*
		Static method which returns the greatest common divisor of
		two integers
		@param a left integer argument
		@param b right integer argument
		@return the gcd of a and b
	*/
	static int gcd(int a, int b)
	{	 
	  assert(a > 0 && b > 0);
	  if(a%b == 0)
		return b;
		
  	  return gcd(b, a%b);
	}

	/*
		Converts the rational number into the inverse of itself
	*/
	void invert();

	/*
		Multiplies the rational number times itself n amount of times
		@param n number of times the rational is multiplied by itself 
	*/
	Rational& toThePower(int n);

	/*
		Returns a Rational that is the product of two Rationals
	*/
	Rational& operator*(const Rational& r) const;

	/*
		Returns a Rational object which is the result of dividing 
		a Rational by a Rational
	*/
	Rational& operator/(const Rational& r) const;

	/*
		Returns a Rational that is the sum of two Rationals
	*/
	Rational& operator+(const Rational& r) const;

	/*
		Returns a Rational that is the difference between two Rationals
	*/
	Rational& operator-(const Rational& r) const;

	/*
		Returns the additive inverse of the current Rational
	*/
	void operator-();

	/*
		The product of two Rationals and assigns the result
		to the Rational on the left
	*/
	void operator*=(const Rational& r);

	/*
		Assigns the quotient of two Rationals to the left operand
	*/
	void operator/=(const Rational& r);

	/*
		Assign the left Rational the result of the sum of the left
		and right Rational
	*/
	void operator+=(const Rational& r);

	/*
		Assign the left Rational the result of the difference of the left
		and right Rational
	*/
	void operator-=(const Rational& r);

	/*
		Increments the value of the Rational by 1 (Prefix)
	*/
	Rational& operator++();

	/*
		Increments the value of the Rational by 1 (Postfix)
	*/
	Rational operator++(int);

	/*
		decrements the value of the Rational by 1 (Prefix)
	*/
	Rational& operator--();

	/*
		decrements the value of the Rational by 1 (Postfix)
	*/
	Rational operator--(int);

	/*
		Returns true if the implicit Rational argument is equal to the
		explicit Rational argument
	*/
	bool operator==(const Rational&);

	/*
		Returns true if the implicit Rational argument is not equal
		to the explicit Rational argument and false otherwise.
	*/
	bool operator!=(const Rational&);

	/*
		Returns true if they implicit Rational argument is less than
		the explicit Rational argument
	*/
	bool operator<(const Rational&);

	/*
		Returns true if they implicit Rational argument is less than
		or equal than the explicit Rational argument and true otherwise
	*/
	bool operator<=(const Rational&);

	/*
		Returns true if they implicit Rational argument is greater than
		the explicit Rational argument
	*/
	bool operator>(const Rational&);

	/*
		Returns true if they implicit Rational argument is greater than
		or equal than the explicit Rational argument
	*/
	bool operator>=(const Rational&);

	/*
		Returns true if the numerator is zero
	*/
	bool operator!();

	/*
		Compares two Rationals for equality. Returns a positive
		integer if the implicit object is greater than the
		explicit aregument. Zero if they are equal. Returns a
		negative integer if the implicit object is less than
		the explicit object argument.
	*/
	int compare(const Rational& r) const;


private:
	int numerator;
	int denominator;
	void setProperForm();

};


ostream& operator<<(ostream& out, const Rational& r);
istream& operator>>(istream& in, Rational& r);

#endif


#include"rational.h"
#include <iostream>
#include <cassert>
#include <cmath>

using namespace std;

Rational::Rational() : numerator(0), denominator(1){}

Rational::Rational(int n) : numerator(n), denominator(1){}

Rational::Rational(int n, int d):numerator(n), denominator(d)
{
	setProperForm();
}

Rational::Rational(double n) : numerator((int)n), denominator(1){}

int Rational::getNumerator() const
{ 
	return numerator;
}

int Rational::getDenominator() const 
{ 
	return denominator;
}

void Rational::print() const
{
	int i = this->getDenominator();
	cout << numerator;
	if(i == 1)
		cout << endl;
	else 
		cout << "/" << denominator << endl;
}

void Rational::print(ostream& out) const
{
	int i = this->getDenominator();
	out << numerator;
	if(i == 1)
		out << endl;
	else 
		out << "/" << denominator << endl;
}

void Rational::setProperForm()
{
	int sign = 1;
	if(numerator < 0)
	{
		sign = -1;
		numerator = -numerator;
	}
	if(denominator < 0)
	{
		sign = -sign;
		denominator = -denominator;
	}

	assert(denominator != 0);
	int d = 1;
	if(numerator > 0) d = gcd(numerator, denominator);
	numerator = sign * (numerator / d);
	denominator = denominator / d;
}

void Rational::invert()
{
	int temp = this->numerator;
	numerator = denominator;
	denominator = temp;
}

Rational& Rational::toThePower(int n)
{
	assert(n > 0);
	int num = numerator;
	int den = denominator;
	static_cast<int>(num) = pow(double(num),n);
	static_cast<int>(den) = pow(double(den),n);
	Rational newRational = Rational(num, den);
	return newRational;
}

ostream& operator<<(ostream& out, const Rational& r)
{
	if(r.getNumerator() == r.getDenominator())
		out << r.getNumerator();
	else
		out << r.getNumerator() << "/" << r.getDenominator();
	return out;
}

istream& operator>>(istream& in, Rational& r)
{
	int num, den;

	in >> num;
	char c;
	in >> c;
	if(c == '/')
		in >> den;
	else
	{
		in.unget();
		den = 1;
	}

	r = Rational(num, den);
	return in;
}

Rational& Rational::operator*(const Rational& r)const
{
	Rational newRational(numerator * r.numerator, denominator * r.denominator);
	return newRational;
}

Rational& Rational::operator/(const Rational& r) const
{
	Rational newRational(numerator*r.denominator,denominator*r.numerator);
	return newRational;
}

Rational& Rational::operator+(const Rational& r) const
{
	Rational newRational(numerator*r.denominator + denominator*r.numerator,
		denominator*r.denominator);
	return newRational;
}

Rational& Rational::operator-(const Rational& r) const
{
	Rational newRational(numerator*r.denominator - r.numerator * denominator, 
		denominator * r.denominator);
	return newRational;
}

void Rational::operator-()
{
	numerator = -numerator;
}

void Rational::operator*=(const Rational& r)
{
	numerator = numerator * r.numerator;
	denominator = denominator * r.denominator;
}

void Rational::operator/=(const Rational& r)
{
	assert(r.numerator != 0); //zero numerator will cause result w/zero denominator
	int num = numerator * r.denominator;
	int den = denominator * r.numerator;
	int d = 1;
	if(num > 0) d = gcd(num, den);
	numerator = num/d;
	denominator = den/d;
}

void Rational::operator+=(const Rational& r)
{
	int d = gcd(denominator,r.denominator);
	int lcd = (denominator*r.denominator)/d;
	int num1 = (lcd/denominator) * numerator;
	int num2 = (lcd/r.denominator) * r.numerator;
	numerator = num1 + num2;
	denominator = lcd;
	this->setProperForm();
}

void Rational::operator-=(const Rational& r)
{
	int d = gcd(denominator,r.denominator);
	int lcd = (denominator*r.denominator)/d;
	int num1 = (lcd/denominator) * numerator;
	int num2 = (lcd/r.denominator) * r.numerator;
	numerator = num1 - num2;
	denominator = lcd;
	this->setProperForm();
}

Rational& Rational::operator++()
{
	numerator+=denominator;
	return *this;
}

Rational Rational::operator++(int dummy)
{
	Rational newRational(numerator, denominator);
	numerator+=denominator;
	return newRational;
}

Rational& Rational::operator--()
{
	numerator-=denominator;
	return *this;
}

Rational Rational::operator--(int)
{
	Rational newRational(numerator, denominator);
	numerator-=denominator;
	return newRational;
}

bool Rational::operator==(const Rational& r)
{
	return compare(r) == 0;
}

bool Rational::operator!=(const Rational& r)
{
	return !compare(r) == 0;
}

bool Rational::operator<(const Rational& r)
{
	return compare(r) < 0;
}

bool Rational::operator<=(const Rational& r)
{
	return compare(r) <= 0;
}

bool Rational::operator>(const Rational& r)
{
	return compare(r) > 0;
}

bool Rational::operator>=(const Rational& r)
{
	return compare(r) >= 0;
}

bool Rational::operator!()
{
	return (numerator==0);
}

int Rational::compare(const Rational& r) const
{
	return ((numerator*r.denominator)-(denominator*r.numerator));
}
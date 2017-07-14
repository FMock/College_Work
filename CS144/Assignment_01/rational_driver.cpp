#include <iostream>
#include <cassert>
#include "rational.h"

using namespace std;
/*
	Frank Mock
	CS144
	Assignment 1

	This is a driver program to test the Rational class.
*/

int main()
{
	//Get input from the user
	int a, b, c;
	cout << "Enter the numerator:";
	cin >> a;
	cout << "Enter the denominator:";
	cin >> b;
	cout << "Enter exponent:";
	cin >> c;

	double d = 6.2;
	Rational ratNum1 = Rational();
	Rational ratNum2 = Rational(d);
	Rational ratNum3 = Rational(a,b);
	ratNum3.print();
	Rational ratNum4 = ratNum3 * ratNum3;
	cout << "ratNum4 = ratNum3 * ratNum3 which equals " << ratNum4 << endl;
	Rational ratNum5 = ratNum3.toThePower(c);
	cout << "ratNum3 to the power of " << c <<" is " << ratNum5 << endl;
	Rational ratNum6 = ratNum3/ratNum4;
	cout << ratNum3 << " / " << ratNum4 << " is " << ratNum6 << endl;
	cout << ratNum3 << " after calling invert is ";
	ratNum3.invert();
	cout << ratNum3 << endl;
	Rational ratNum7 = ratNum3 + ratNum4;
	cout << ratNum3 << " + " << ratNum4 << " is " << ratNum7 << endl;
	Rational ratNum8 = ratNum3 - ratNum4;
	cout << ratNum3 << " - " << ratNum4 << " is " << ratNum8 << endl;
	Rational temp = Rational(ratNum3.getNumerator(),ratNum3.getDenominator());
	-ratNum3;
	cout << "-"<< temp << " is " << ratNum3 << endl;
	cout << ratNum3 << "*="<< ratNum3 << " is ";
	ratNum3*=ratNum3;
	cout << ratNum3 << endl;
	cout << ratNum3 << "/="<< ratNum3 << " is ";
	ratNum3/=ratNum3;//result should be 1
	cout << ratNum3 << endl;
	cout << ratNum3 << "+=" << ratNum4 << " is ";
	ratNum3+=ratNum4;
	cout << ratNum3 << endl;
	cout << ratNum3 << "-=" << ratNum4 << " is ";
	ratNum3-=ratNum4;//ratNum3 should equal 1 again
	cout << ratNum3 << endl;
	cout << ratNum3 << "++" << " is ";
	ratNum3++;
	cout << ratNum3 << endl;
	cout << ratNum3 << "--" << " is ";
	ratNum3--;
	cout << ratNum3 << endl;
	cout << ratNum3 << "==" << ratNum3 << " is ";
	if(ratNum3==ratNum3)
		cout << "True" << endl;//should output true
	else
		cout << "False" << endl;
	cout << ratNum3 << "==" << ratNum4 << " is ";
	if(ratNum3==ratNum4)
		cout << "True" << endl;
	else
		cout << "False" << endl;//should output false
	cout << ratNum3 << "!=" << ratNum4 << " is ";
	if(ratNum3!=ratNum4)
		cout << "True" << endl;//should cout true since it is true they are not equal
	else
		cout << "False" << endl;
	cout << ratNum3 << "<" << ratNum4 << " is ";
	if(ratNum3<ratNum4)
		cout << "True" << endl;
	else
		cout << "False" << endl;
	cout << ratNum3 << "<=" << ratNum4 << " is ";
	if(ratNum3<=ratNum4)
		cout << "True" << endl;
	else
		cout << "False" << endl;
	cout << "GCD of " << a << " and " << b << " is " << Rational::gcd(a,b) << endl;
	system("pause");
	return 0;
}


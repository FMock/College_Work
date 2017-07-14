#include<iostream>
#include"polynomial.h"

using namespace std;
/*
	Frank Mock CS144
	project 1 - Exercise P12.14 Polynomial class

	This program will test the polynomial member functions add,
	multiply and print.

	The Polynomial class is a linked list in disguise. The Polynomial
	is the linked list and the terms are the nodes.

	If time allowed I would improve the multiply member function by
	collecting like terms before returning the polynomial
*/

int main()
{
	//create a polynomial 2x^2
	Polynomial p(Term(2, 2));
	cout << "created polynomial 2x^2" << endl;
	p.print();
	cout << "multiplying it by itself 2x^2 * 2x^2" << endl;
	//multiply it by itself 2x^2 * 2x^2
	Polynomial product = p.multiply(p);
	product.print();//expected 4x^4
	//add the term -2x^2 to the polynomial p
	cout << "Adding the term -2x^2 to the existing polynomial" << endl;
	p.add(Polynomial(Term(-2, 2)));
	//print out p - expected -2x^2+2x^2
	p.print();
	//The size of the polynomial (list of terms) is now 2
	cout << "The size of the polynomial (list of terms) is " << p.get_size() << endl;
	//add two additional terms
	cout << "Adding two terms -3x^1 and 9x^9" << endl;
	p.add(Polynomial(Term(-3, 1)));
	p.add(Polynomial(Term(9, 9)));
	p.print();//expected 9x^9-3x^3-2x^2+2x^2
	cout << "The size of the polynomial (list of terms) is " << p.get_size() << endl;
	//Multiply the polynomial p by itself. Result will be very big polynomial
	cout << "Multiply the polynomial p by itself. Result will be very big polynomial" << endl;
	cout << "9x^9-3x^3-2x^2+2x^2 * 9x^9-3x^3-2x^2+2x^2 = " << endl;
	Polynomial m = p.multiply(p);
	m.print();//a very big polynomial 
	/*
		If time allowed I would improve the multiply member by having it
		combine like terms before returning the polynomial
	*/
	cout << "This can be improved by combining like terms" << endl;
	string endProgram;
	cout << "Press a key to end";
	cin >> endProgram;
	return 0;
}
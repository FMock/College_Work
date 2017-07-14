#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include<cassert>
#include<string>
#include<iostream>

using namespace std;

/*
	Frank Mock CS144
	Project 1 - P12.14 page 502

	Polynomial class which is a double linked list in disguise
	Users of this class can add, multiply and print polynomials

	If I had more time, I would improve the muliply member by
	having it collect like terms so the polynomial it returns
	is smaller in size.
*/

class Polynomial;
class Iterator;

class Term
{
public:
        Term(int, int); //constructs a Term with a given data value.
		Term(const Term&);//copy constructor
		int compare(const Term& right) const;
		void setCoefficient(int);
		void setExponent(int);
		friend ostream& operator<<(ostream&, Term&);
		friend Term& operator*(const Term&, const Term&);

private:
        int coefficient;
		int exponent;
        Term* previous;
        Term* next;
        friend class Polynomial;
        friend class Iterator;
};


class Polynomial
{
public:

    Polynomial(); //Constructs an empty Polynomial;

	Polynomial(Term);

	Polynomial(int coef, int expo); //Constructs a polynomial with a single term

	Polynomial(const Polynomial&); //Copy Constructor

	void add(const Polynomial&); //Add a term to the front of the Polynomial

	Polynomial& multiply(Polynomial&); //multiply two polynomials

	void print();

    int get_size(); //Computes the number of elements in the Polynomial

private:
        Term* first;
        Term* last;
        friend class Iterator;
};


class Iterator
{
public:

        Iterator(); //Constructs an iterator that does not point into any Polynomial.

        Term get() const; //Looks up the value at a position.

        void next(); //Advances the iterator to the next Term.

        void previous(); //Moves the iterator to the previous Term.

        bool equals(Iterator b) const; //Compares two iterators

private:
        Term* position;
        Polynomial* container;
        friend class Polynomial;
};

#endif


#include<cmath>
#include "polynomial.h"

/*
	Copy Constructor
	@param t the Term to be copied
*/
Term::Term(const Term& t)
{
	exponent = t.exponent;
	coefficient = t.coefficient;
	previous = t.previous;
	next = t.next;
}
/*
	Constructs a term
	@param coef the coefficient
	@param expo the power of X
*/
Term::Term(int coef, int expo)
{
    coefficient = coef;
	exponent = expo;
    previous = NULL;
    next = NULL;
}

ostream& operator<<(ostream& out, Term& t)
{
	if(t.coefficient == 1)
		return out << "X^" << t.exponent;
	else if(t.coefficient == -1)
		return out << "-X^" << t.exponent;
	else
		return out << t.coefficient << "X^" << t.exponent;
}

/*
	Overloaded * operator to aid in multiplying two polynomial terms
	@param a the left operand
	@param b the right operand
	@return the Term that is the product of the two parameter terms
*/
Term& operator*(const Term& a, const Term& b)
{
	int c = a.coefficient*b.coefficient;
	int e = a.exponent+b.exponent;
	Term* t = new Term(c, e);
	return *t;
}


/*
	Compares one Term to another
*/
int Term::compare(const Term& right) const
{
	int result = static_cast<int>(pow(static_cast<double>(this->coefficient), this->exponent)
		- pow(static_cast<double>(right.coefficient), right.exponent));
	return result;
}

bool operator!=(const Term& a, const Term& b)
{
	return a.compare(b) != 0;
}

/*
	Constructs an empty polynomial
*/
Polynomial::Polynomial()
{
     first = NULL;
     last = NULL;
}

/*
	Constructs a polynomial from a single term
	@param aTerm a Term object
*/
Polynomial::Polynomial(Term aTerm)
{
	Term* new_Term = new Term(aTerm.coefficient, aTerm.exponent);
	first = new_Term;
	last = new_Term;
}

/*
	Constructs a polynomial with a new term
	@param coef The coefficient of the term
	@param expo The exponent of the term
*/
Polynomial::Polynomial(int coef, int expo)
{
	Term* new_Term = new Term(coef, expo);
	first = new_Term;
	last = new_Term;
}

/*
	Copy constructor
	@param aPoly The polynomial that will be copied
*/
Polynomial::Polynomial(const Polynomial& aPoly)
{
	first = aPoly.first;
	last = aPoly.last;
}

/*
	Add a new term to an exisiting polynomial
*/
void Polynomial::add(const Polynomial& aPoly)
{
    Term* new_Term = new Term(aPoly.first->coefficient, aPoly.first->exponent);

    if(last == NULL)//empty polynomial
    {
        this->first = new_Term;
        this->last = new_Term;
    }
    else
    {
        new_Term->next = first;
        first->previous = new_Term;
        this->first = new_Term;
    }
}

/*
	Multiplies two polynomials
	@param p the polynomial that gets multiplied by the implicit polynomial
	@return the polynomial that is the product of the two polynomials
*/
Polynomial& Polynomial::multiply(Polynomial& p)
{
	Polynomial* poly = new Polynomial(); //Create a new Polynomial pointer to return
	Iterator left; //points to the implicit poly
	Iterator right;//points to the explicit poly
	left.container = this;
	left.position = this->first;
	right.container = &p;
	right.position = p.first;
	while(left.position != NULL)//iterates over left polynomial terms
	{
		while(right.position != NULL)//iterates over right polynomial terms
		{
			poly->add(left.get()*right.get());
			right.position = right.position->next;
		}
		right.position = p.first;//move right poly iterator back to begining
		left.position = left.position->next;//move left poly iterator to next position
	}
	return *poly;
}

/*
	Returns the number terms in the polynomial (number of elements in linked list)
*/
int Polynomial::get_size()
{
    int counter = 0;
    Iterator iter;
    iter.container = this;
    iter.position = this->first;

    //If the Polynomial is empty return counter = 0;
    if(this->last == NULL)
      return counter;

    while(iter.position != NULL)
    {
        counter++;
        iter.position = iter.position->next;
    }

    return counter;
}
/*
	Prints out the polynomial (prints all terms)
*/
void Polynomial::print()
{
	Iterator iter;
	iter.position = this->first;
	cout << iter.get();
	iter.next();
	while(iter.position != NULL)
	{
		if(iter.get().coefficient > 0)
			cout << "+";
		cout << iter.get();
		iter.next();
	}
	cout << endl;
}

Iterator::Iterator()
{
        position = NULL;
        container = NULL;
}

Term Iterator::get() const
{
        assert(position != NULL);
		int coef = position->coefficient;
		int expo = position->exponent;
		Term new_Term = Term(coef, expo);
        return new_Term;
}

void Iterator::next()
{
        assert(position != NULL);
        position = position->next;
}

void Iterator::previous()
{
        assert(position != container->first);
        if (position == NULL)
                position = container->last;
        else
                position = position->previous;
}

bool Iterator::equals(Iterator b) const
{
        return position == b.position;
}


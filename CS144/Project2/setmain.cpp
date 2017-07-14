#include"set.h"
#include<iostream>
#include<string>
#include<sstream>
using namespace std;
/*
	Frank Mock
	CS144 Project2
	Testing the generic class set that was created for this project
*/

/*
	A class named Dog made strictly for testing the generic set class
*/
class Dog
{
public:
	Dog()
	{
		counter++;
		ostringstream oss;
		oss << "Dog " << counter;
		name = oss.str();
	};

	int compare(const Dog& right)
	{
		return getName().compare(right.getName());
	}

	string getName()const {return name;}
	string name;

private:
	static int counter;
};
//initialize static Dog counter
int Dog::counter = 0;

bool operator==(const Dog& left, const Dog& right)
{
	return left.getName() == right.getName();
}

ostream& operator<<(ostream& out, const Dog& d)
{
	out << d.getName();
	return out;
}

int main()
{
	//Make a new set to hold variables of type int
	set<int> intSet;
	cout << "Created a integer set" << endl;
	cout << "Adding 0 - 7 to the set" << endl;
	const int SIZE = 8;
	for(size_t i = 0; i < SIZE; i++)
		intSet.add(i);
	cout << "Number of elements in the set: " << intSet.numElts() << endl;
	cout << "Using getElts() to get an array of the set contents" << endl;
	int* t = intSet.getElts();
	cout << "Printing elements in the array" << endl;
	for(size_t j = 0; j < SIZE; j++)
		cout << *t++ << " ";
	cout << endl;
	cout << "Removing zero and even numbers from the set" << endl;
	for(size_t i = 0; i < SIZE; i++)
		if(i%2 == 0)
			intSet.remove(i);
	cout << "Number of elements in the set: " << intSet.numElts() << endl;
	if(intSet.contains(2))
		cout << "Did not delete 2!" << endl;
	else
		cout << "The number 2 has been deleted from the set" << endl;

	cout<< "Creating a new set to hold strings" << endl;
	//Make a new set to hold variables of type string
	set<string> strSet;
	for(size_t i = 0; i < SIZE; i++)
	{
		ostringstream oss;
		oss << i;
		strSet.add(oss.str());
	}
	cout<< "Added the string numbers 0 - 7" << endl;
	cout << "Number of elements in the set: " << strSet.numElts() << endl;
	cout << "Using getElts() to get an array of the set contents" << endl;
	string* s = strSet.getElts();
	cout << "Printing elements in the array" << endl;
	for(size_t j = 0; j < SIZE; j++)
		cout << *s++ << " ";
	cout << endl;
	if(strSet.contains("7"))
		cout << "The set contains 7" << endl;
	else
		cout << "The set does not contain 7" << endl;

	//Creating a new set to hold Dog objects
	cout << "Creating a new set to hold Dog objects" << endl;
	set<Dog> dogSet;
	Dog dog1;
	Dog dog2;
	Dog dog3;
	Dog dog4;
	dogSet.add(dog1);
	dogSet.add(dog2);
	dogSet.add(dog3);
	dogSet.add(dog4);
	cout << "Added 4 dogs to the set" << endl;
	cout << "The size of the set of Dogs " << dogSet.numElts() << endl;
	cout << "Try to add Dog 2 to the set again (should not add)" << endl;
	dogSet.add(dog2);//should not be added to the set
	cout << "The size of the set of Dogs " << dogSet.numElts() << endl;
	cout << "Using getElts() to get array of set contents" << endl;
	cout << "Printing out the array" << endl;
	Dog* g = dogSet.getElts();
	for(size_t i = 0; i < 4; i++)
		cout << *g++ << endl;
	cout << "Removing Dog 2 from the set" << endl;
	dogSet.remove(dog2);
	if(dogSet.contains(dog2))
		cout << "The set contains Dog 2" << endl;
	else
		cout << "The set does not contain Dog 2" << endl;
	string endk;
	cout << "Press any letter key and then enter to exit: ";
	cin >> endk;
	return 0;
}
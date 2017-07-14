#include<iostream>
#include"stack.h"

/*
	Frank Mock CS144
	Project 1 - Exercise P12.15

	This program tests the stack abstract data type
*/


using namespace std;

int main()
{
	//Create a stack and add three names - check push member function
	stack s;
	cout << "Testing push - Add three names (strings) to the stack" << endl;
	s.push("Frank");
	s.push("Debbie");
	s.push("Sydney");

	//check the size member function
	int size = s.size();
	cout << "The size of the stack is: " << size << endl;//expected size = 3

	//Get the top name from the list. Since LIFO expected is Sydney
	string name = s.top();
	cout << "Name at the top of the stack is: " << name << endl;

	//Remove the top item from the stack
	s.pop();
	size = s.size();
	cout << "Removed the top name from the stack" << endl;
	cout << "The size of the stack is: " << size << endl;//expected size = 2

	//Now Debbie should be at the top of the stack
	name = s.top(); //expected: name = Debbie
	cout << "Name at the top of the stack is: " << name << endl;

	//remove all names from the stack
	while(s.size() > 0)
		s.pop();
	cout << "Removed all names from stack" << endl;

	//empty member should return true
	if(s.empty())
		cout << "The stack is empty" << endl;
	else
		cout << "The stack is not empty" << endl;

	string end_Program;
	cout << "Press a key to end" << endl;
	cin >> end_Program;
	return 0;
}
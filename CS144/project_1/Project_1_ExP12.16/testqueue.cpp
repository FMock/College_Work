#include<iostream>
#include<sstream>
#include"queue.h"

using namespace std;
/*
	Frank Mock CS144
	Project 1 - Exercise P12.16

	This program tests the operations of the queue class
	The queue class uses a linked list of strings as the underlying container
*/

int main()
{
	queue q;//create a queue

	//add ten strings to the queue
	for(int i = 1; i <= 10; i++)
	{
		stringstream ss;
		ss << "Number " <<  i;
		q.push(ss.str());
	}
	//The size of the queue should now be 10
	cout << "The size of the queue is: " << q.size() << endl;

	//Item at the front of the queue should be "Number 1"
	string n = q.front();
	cout << "The item at the front on the queue is " << n << endl;

	//Remove "Number 1" from the front of the queue. testing pop
	q.pop();
	cout << "Popped the front item from the queue" << endl;

	n = q.front(); //expected n = "Number 2"
	cout << "The item at the front of the queue is now " << n << endl;

	//Remove "Number 2" from the front of the queue. testing pop
	q.pop();
	cout << "Popped the front item from the queue" << endl;

	n = q.front(); //expected n = "Number 3"
	cout << "The item at the front of the queue is now " << n << endl;

	//The most recent addition to the queue is "Number 10"
	//The back member should return the string "NUmber 10"
	cout << "The item at the back of the queue is " << q.back() << endl;

	//Test Empty. Pop all the items in the queue and test empty member
	cout << "Popping all items out of the queue" << endl;
	while(q.size() > 0)
		q.pop();
	if(q.empty())
		cout << "The queue is empty" << endl;//expected outcome
	else
		cout << "The queue is not empty" << endl;

	string endProgram;
	cout << "Press a key to end program: ";
	cin >> endProgram;
	return 0;
}

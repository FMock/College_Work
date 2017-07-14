#include<cassert>
#include<string>
#include<iostream>

using namespace std;

/*
	Frank Mock CS144
	Project 1 - Exercise P12.16

	A double linked list for the string data type
*/


class List;
class Iterator;

class Node
{
public:
        /** 
        Constructs a node with a given data value.
        */
        Node(string);

private:
        string data;
        Node* previous;
        Node* next;
        friend class List;
        friend class Iterator;
};


class List
{
public:

       List(); //Constructs an empty list;

       void push_back(string data); //Appends an element to the list.

       void insert(Iterator iter, string i); //Inserts an element into the list.

       Iterator erase(Iterator iter); //Removes an element from the list.

       Iterator begin(); //Gets the beginning position of the list.

       Iterator end(); //Gets the past-the-end position of the list.

	void reverse(); //Reverses the items in a list
    
    void push_front(string); //Adds an integer value to front of the list
    
    int get_size(); //Computes the number of elements in the list
    
private:
        Node* first;
        Node* last;
        friend class Iterator;
};


class Iterator
{
public:

        Iterator(); //Constructs an iterator that does not point into any list.

        string get() const; //Looks up the value at a position.

        void next(); //Advances the iterator to the next node.

        void previous(); //Moves the iterator to the previous node.

        bool equals(Iterator b) const; //Compares two iterators

private:
        Node* position;
        List* container;
        friend class List;
};


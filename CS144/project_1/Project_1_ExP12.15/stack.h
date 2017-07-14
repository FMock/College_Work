#include <iostream>
#include <string>
#include "LList.h"
using namespace std;

#ifndef TSTACK_H
#define TSTACK_H
/*
	Frank Mock CS144
	Project 1 - Exercise P12.15

	This stack implementation uses a double linked list as a container
*/


class stack
{
    
public:
      /** Constructs an initially empty stack. */
      stack();

      /** Pushes an item onto the top of the stack.
          @param item The item to be inserted
      */
      void push(const string& item);

      /** Returns a reference to the object at the top of the stack 
          without removing it.
          @return A reference to the object at the top of the stack
      */
      string top();

      /** Removes the top item from the stack. */
      void pop();

      /** Determines whether the stack is empty. */
      bool empty();

      /** Returns the number of items in the stack. */
      int size();

private:

      /** A pointer to the top of the stack */
      Node* top_of_stack;

      /** A sequential container to contain the stack items */
      List container;  
  };
#endif
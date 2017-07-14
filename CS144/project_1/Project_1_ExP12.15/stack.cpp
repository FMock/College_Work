#include <iostream>
#include "stack.h"

/** Construct an initially empty stack. */
  stack::stack(){}

/** Puts an item onto the top of the stack.
    @param item The item to be inserted
*/
  void stack::push(const string& item)
  {
	  Iterator iter = container.begin();
	  container.insert(iter, item);
  }

/** Returns a reference to the object at the top of the stack 
    without removing it.
    @return A reference to the object at the top of the stack
*/
  string stack::top()
  {
	  Iterator iter;
	  iter = container.begin();
	  string s = iter.get();
	  return s;
  }


/** Removes the top item from the stack.
 */
  void stack::pop()
  {
	  Iterator iter = container.begin();
	  container.erase(iter);
  }

/** Determines whether the stack is empty. */
  bool stack::empty()
  {
	  int s = container.get_size();
	  if(s == 0)
		  return true;
	  else
		  return false;
  }

/** Returns the number of items in the stack. */
  int stack::size()
  {
	  return container.get_size();
  }

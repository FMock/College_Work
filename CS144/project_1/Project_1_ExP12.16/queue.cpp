#include <iostream>
#include "queue.h"

/** Construct an initially empty queue. */
  queue::queue(){}

/** Puts an item at the end of the queue.
    @param item The item to be inserted
*/
  void queue::push(const string& item)
  {
	  Iterator iter = container.end();
	  container.insert(iter, item);
  }

/** Returns a reference to the object at the front of the queue 
    without removing it.
    @return A reference to the object at the front of the queue
*/
  string queue::front()
  {
	  Iterator iter = container.begin();
	  string s = iter.get();
	  return s;
  }

/** Returns a reference to the object at the back of the queue 
    without removing it.
    @return A reference to the object at the back of the queue
*/
  string queue::back()
  {
	  Iterator iter = container.end();
	  iter.previous();
	  string s = iter.get();
	  return s;
  }

/** Removes the item at the front of the queue.
 */
  void queue::pop()
  {
	  Iterator iter = container.begin();
	  container.erase(iter);
  }

/** Determines whether the queue is empty. */
  bool queue::empty()
  {
	  int s = container.get_size();
	  if(s == 0)
		  return true;
	  else
		  return false;
  }

/** Returns the number of items in the queue. */
  int queue::size()
  {
	  return container.get_size();
  }

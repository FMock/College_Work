#include <iostream>
#include <string>
#include "llist.h"
using namespace std;

#ifndef QUEUE_H
#define QUEUE_H
/*
	Frank Mock CS144
	Project 1 - Exercise P12.16

	This queue implementation uses a double linked list as a container
*/


class queue
{
    
public:
      /** Constructs an initially empty queue. */
      queue();

      /** Pushes an item into the back of the queue.
          @param item The item to be inserted
      */
      void push(const string& item);

      /** Returns a reference to the object in the front of the queue 
          without removing it.
          @return A reference to the object in the front of the queue
      */
      string front();

	  /** Returns a reference to the object in the back of the queue 
          without removing it.
          @return A reference to the object in the back of the queue
      */
      string back();

      /** Removes the front item from the queue (oldest inserted item)*/
      void pop();

      /** Determines whether the queue is empty. */
      bool empty();

      /** Returns the number of items in the queue. */
      int size();

private:

      /** A pointer to the front of the queue */
      Node* front_of_queue;

      /** A sequential container to contain the queue items */
      List container;  
  };
#endif
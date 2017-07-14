#ifndef BOWLING_SHOE_SHELF_H
#define BOWLING_SHOE_SHELF_H

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#include <iostream>

/*
	Frank Mock
	CS144 Project 3
	BowlingShoeShelf represents a shoe shelf at a bowling alley. There
	are only a limited number of shoes on the shelf. The shoeShelf array
	represents the shelf where the pairs of shoes are stored. The mutex
	object ensures only one thread has access to the shoe shelf at a time.
	Anytime shoes are aquired or released the mutex is locked and then
	unlocked when it is finished. If a thread tries to aquire shoes and
	the shoe count is zero (empty shelf) the requesting thread will wait
	until the shelf condition changes and a pair of shoes can be issued.
	The same waiting occurs if the shoe shelf is full. A returning thread
	must wait until a pair of shoes is aquired until a pair can be returned
	since we can not have more shoes on the shelf then 8 at a time.
*/

class BowlingShoeShelf
{
public:  
	//mutex object to help control concurrent access to resource (shoe array)
	boost::mutex io_mutex;

	//Constructor
	BowlingShoeShelf(): a(0), b(0), shoeCount(0){} 

	/*
		facilitates a thread returning a pair of shoes from the shoe array.
		A pair of shoes can not be returned if the shelf is already full.
		If this is the case, the thread must wait until another thread
		removes a pair of shoes.
	*/
	void release(int m)
	{   
		boost::mutex::scoped_lock lock(mutex); //used to lock the mutex
	
		if (shoeCount == NUM_SHOES)//can't return shoes when the shelf is full    
		{      
			{   
				//lock so another thread can not access resource (array of shoes)
				boost::mutex::scoped_lock lock(io_mutex);        
				std::cout << "BowlingShoeShelf is full. Waiting for bowlers" << std::endl;      
			}      
			while (shoeCount == NUM_SHOES)        
				cond.wait(lock);    
		}

		shoeShelf[a] = m; //return shoes to it's spot on the shelf (array)
		a = (a + 1) % NUM_SHOES; // ensure array index stays in bounds    
		++shoeCount; //one more pair is available   
		cond.notify_one(); //notify that the condition has been met 
	}
	
	/*
		facilitates a thread recieivng a pair of shoes from the shoe array.
		If the shelf is empty the thread must wait until a pair of shoes is
		returned before it may aquire shoes.
	*/
	int aquire()
	{    
		boost::mutex::scoped_lock mlock(mutex);//used to lock the mutex

		if (shoeCount == 0)//if the shelf is empty, the thread must wait for shoes    
		{      
			{   
				//lock so another thread can not access resource (array of shoes)
				boost::mutex::scoped_lock lock(io_mutex);        
				std::cout << "BowlingShoeShelf is empty. Waiting for returns" << std::endl;      
			}      while (shoeCount == 0)        
					cond.wait(mlock);    
		}

		/*
			If we get here, the condition has been met and a pair of shoes may
			be issued to the bowler.
		*/
		int i = shoeShelf[b]; //remove a pair of shoes from the shelf   
		b = (b + 1) % NUM_SHOES; //ensure index doesn't go out of range
		--shoeCount;//one less pair is available  
		cond.notify_one(); //notify that the condition has been met  
		return i;  
	}     
private:
	//mutex object to facilitate concurrent resource access
	boost::mutex mutex;
	//condition object to ensure the resource (shoe array)
	//is in a proper condition for thread action
	boost::condition cond;
	//index variables for resource
	unsigned int a, b, shoeCount;
	//Number of resources available is two plus this number
	static const int NUM_SHOES = 6;//8
	//The thread resource is an integer array that represents the
	//shoes on the shelf.
	int shoeShelf[NUM_SHOES - 1];
};

#endif
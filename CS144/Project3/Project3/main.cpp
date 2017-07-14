#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <iostream>
#include"bowling_shoe_shelf.h"

/*
	Frank Mock
	CS144
	Project 3

	The object pool is managed by the BowlingShoeShelf class. This
	class contains a resource which is an array of integers that
	represent bowling shoes. The resource is of a fixed size and
	so a thread may have to wait until the resource is in a
	condition to satisfy the demand of the thread.
*/

int bowlers = 75; //number of bowlers
boost::mutex io_mutex; //help control concurrent access of resource
BowlingShoeShelf shoeShelf; //Object which contains the resource

//method to simulate bowlers returning shoes
void returnShoes()
{  
	for(int i = 0; i < bowlers; ++i)  
	{    
		{      
			boost::mutex::scoped_lock lock(io_mutex);      
			std::cout << "Return shoes: " << i + 1 << std::endl;    
		}    
		shoeShelf.release(i);  
	}
}

//method to simulate bowlers getting a pair of shoes
void aquireShoes()
{  
	for(int j = 0; j < bowlers; ++j)  
	{    
		int shoes = shoeShelf.aquire();    
		{      
			boost::mutex::scoped_lock lock(io_mutex);      
			std::cout << "aquire shoes: " << shoes + 1 << std::endl;    
		}  
	}
}     

int main()
{  
	/*
		The following two threads will be working at the same time.
		Since aquireShoes and return shoes both contain for loops
		to simulate bowlers aquiring and returning shoes, the threads
		will end up waiting for each other if the resource is being
		used by the other, or in the resource is not in a condition
		the thread requires.
	*/
	boost::thread thread1(&aquireShoes);  
	boost::thread thread2(&returnShoes); 

	thread1.join(); //join the main thread
	thread2.join(); //join the main thread

	std::cin.get(); //wait for input to exit
	return 0;
}
#ifndef SET_H_
#define SET_H_
/*
	Frank Mock
	CS144 Project2
*/
#include <vector>
#include <string>
 
template<typename T>
class set{
    
public:
    
	//Constructs an empty set.
    set();

    /** Adds an item to the set.
        @param item The item to be inserted
    */
	void add(const T& item);

    /**Removes an item from the set.
	   @param item the item to remove
	*/
    void remove(const T& item);

	/**Determines if an item is in the set
	   @param item the item in question
	   @return true if in the set, false otherwise
	*/
	bool contains(const T& item)const;

    //Returns the number of items in the set.
    size_t numElts() const;

	/**Returns a pointer to a dynamically allocated array containing
	   the elements.
	   @return T* pointer to the array that contains the elements
	*/
	T* getElts()const;

	//Determines whether the set is empty.
    bool empty() const;

private:

    std::vector<T> container;
};

//Construct an empty set.
template<typename T>
  set<T>::set(){}

/**Adds an item to the set. If the item is already
   in the set nothing happens.
   @param item The item to be added
*/
template<typename T>
  void set<T>::add(const T& item)
  {
		if(!set<T>::contains(item))
			container.push_back(item);
  }

/**Removes an item from the set
   @param item the item to remove
*/
template<typename T>
  void set<T>::remove(const T& item)
  {
	  for(size_t i = 0; i < container.size(); i++)
	  {
		  if(container.at(i) == item)
			  container.erase(container.begin() + i);
	  }
  }

/**Determines if an item is in the set
   @param item the item in question
   @return true if in the set, false otherwise
*/
template<typename T>
  bool set<T>::contains(const T& item)const
  {
	  //if the undelining container is empty item can not be in it
	  if(container.empty())
		  return false;

	  for(size_t i = 0; i < container.size(); i++)
	  {
		if(container[i] == item)
			return true;
	  }
	  return false;
  }

/**Returns a pointer to a dynamically allocated array containing
   the elements.
   @return T* pointer to the array that contains the elements
*/
template<typename T>
  T* set<T>::getElts()const
  {
	  T* arrayPtr = new T[container.size()];
	  for(size_t i = 0; i < container.size(); i++)
		  arrayPtr[i] = container.at(i);
	  return arrayPtr;
  }

/**Determines whether the set is empty.
   @return true if empty, false otherwise
*/
template<typename T>
  bool set<T>::empty() const
  {
    return container.empty();
  }

/**Returns the number of items in the set.
 @return the number of items in the set
*/
template<typename T>
  size_t set<T>::numElts() const
  {
    return container.size();
  }

#endif
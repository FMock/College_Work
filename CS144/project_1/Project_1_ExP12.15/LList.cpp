#include "LList.h"
#include<string>
using namespace std;

Node::Node(string i)
{  
        data = i;
        previous = NULL;
        next = NULL;
}

List::List()
{  
        first = NULL;
        last = NULL;
}

void List::push_back(string data)
{  
        Node* new_node = new Node(data);
        if (last == NULL) // List is empty
        {  
                first = new_node;
                last = new_node;
        }
        else
        {  
                new_node->previous = last;
                last->next = new_node;
                last = new_node;
        }
}

void List::insert(Iterator iter, string i)
{  
        if (iter.position == NULL)
        {  
                push_back(i);
                return;
        }

        Node* after = iter.position;
        Node* before = after->previous;
        Node* new_node = new Node(i);
        new_node->previous = before;
        new_node->next = after;
        after->previous = new_node;
        if (before == NULL) // Insert at beginning
                first = new_node;
        else
                before->next = new_node;
}

Iterator List::erase(Iterator iter)
{  
        assert(iter.position != NULL);
        Node* remove = iter.position;
        Node* before = remove->previous;
        Node* after = remove->next;
        if (remove == first)
            first = after;
        else
            before->next = after;
        if (remove == last)
                last = before;
        else
                after->previous = before;
                delete remove;
                Iterator r;
                r.position = after;
                r.container = this;
                return r;
}

Iterator List::begin()
{  
        Iterator iter;
        iter.position = first;
        iter.container = this;
        return iter;
}

Iterator List::end()
{  
        Iterator iter;
        iter.position = NULL;
        iter.container = this;
        return iter;
}

void List::reverse()
{
        //Create two pointers to node objects
        Node* current;
        Node* temp;

        //Point both node pointers to the first node in the list
        current = this->first;
        temp = this->first;

        while(current != NULL)
        {
                //Advance the temp node to the node current's next pointer is pointing to
                temp = current->next;

                //Swap what the next and previous pointers point to
                current->next = current->previous;
                current->previous = temp;

                //Advance current node to the node current's previous pointer is pointing to 
                current = current->previous;
        }

        //Swap what the list pointers first and last point to
        temp = this->first;
        this->first = this->last;
        this->last = temp;
}

//Inserts an item at the front of the list
void List::push_front(string data)
{
    Node* new_node = new Node(data);
    
    if(last == NULL)
    {
        this->first = new_node;
        this->last = new_node;
    }
    else
    {
        new_node->next = first;
        first->previous = new_node;
        this->first = new_node;      
    }
}

//Returns the size of the list
int List::get_size()
{
    int counter = 0;;
    Iterator iter;
    iter.container = this;
    iter.position = this->first;
    
    //If the list is empty return counter = 0;
    if(this->last == NULL)
      return counter;

    while(iter.position != NULL)
    {
        counter++;
        iter.position = iter.position->next;
    }
    
    return counter;
}

//Iterator constructor
Iterator::Iterator()
{  
        position = NULL;
        container = NULL;
}

//Returns the item the iterator is pointing at
string Iterator::get() const
{  
        assert(position != NULL);
        return position->data;
}

//Advances the iterator to the next position
void Iterator::next()
{  
        assert(position != NULL);
        position = position->next;
}

//Reverses an iterator one position
void Iterator::previous()
{  
        assert(position != container->first);
        if (position == NULL)
                position = container->last;
        else 
                position = position->previous;
}

//Compares two iterators
bool Iterator::equals(Iterator b) const
{  
        return position == b.position;
}



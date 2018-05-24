// implementation file for the LinkedList class

#include "LinkedList.h"
#include <iostream>
#include <cassert>
using namespace std;

// g++ -c LinkedList.cpp - just compiles this file
// Node() constructor: initialize the data members with default values
LinkedList::Node::Node()
{
   data = 0;
   next = 0;// points nowhere (null pointer)
}

// Default constructor for the linked list 
// initializes the data members of a new, empty list object
LinkedList::LinkedList()
{
    first = 0;
    mySize = 0;                    
}

// destructor
// Traverse the list and deallocate memory for each node in the list
// T(N) = O()
LinkedList::~LinkedList()
{

   // declare a pointer to Node
   Node *ptr = 0;
   // loop while first ! = 0
   while (first != 0)
    {
	  	// 0. ptr point to first Node
	  	ptr = first;
		// 1. make first point to the next node in the list (keep a connection
		// with the remaining list nodes
		first = first->next;
		// 2. deallocate memory for the node pointed by ptr
		delete ptr;   
    }
}


// copy constructor = instantiates a new object as a copy of an 
// existing object
// LinkedList l1(l2);
LinkedList::LinkedList(const LinkedList &old)
{
   // if old list is empty, then just initialize first and mySize to 0
    if (old.first == 0)
	{
       first = 0;
       mySize = 0;
 	}   
   else
   {
   
   	  /* WHILE (there are nodes to visit in old)
   	  		- allocate memory for a new node
   	  		- copy data from the old list node to the new node (data part)
   	  		- link the new node to the end of the calling list object 
   	  		- advance to the next node in old list
   	     ENDWHILE
   	     mySize = old.mySize;
   	   */  
   	  // declare three pointers: 
	  // ptrOld = to traverse the old list
	  // ptr = to point to the last node of the new list
	  // ptrNew = to point to a new node
      Node *ptrOld, *ptr, *ptrNew;
      
      first = ptr = 0;
      ptrOld = old.first; // ptrOld used to traverse the old list node by node
      while (ptrOld != 0)
      {
      	  // 1. allocate memory for a new node
      	  ptrNew = new Node();
      	  // 2. copy data from the old list node to the new node (data part)
      	  ptrNew->data = ptrOld->data;
      	  // 3. link the new node to the end of the calling list object 
      	  // if first node then change value of first
      	  if (first == 0)
      	  {
      	  	   first = ptrNew;
			   ptr = first;
		  }
		  else // add a new node at the end of a non-empty list, 
		  	   // ptr points to the last node
		  {
		  	    // connect last node in the new list to the new node
		  	    ptr->next = ptrNew;
		  	    // move ptr to point to the new node
		  	    ptr = ptr->next; // or ptrNew
		  }
      	  // 4. advance to the next node in old list
      	  ptrOld = ptrOld->next;
      }
      
      mySize = old.mySize;
      
	}					 
} // end copy constructor


// Assignment operator (operator=)
// code: l1 = l2;  l1 will be a linked list object identical to l2
// compiler generated call to operator= function: l1.operator=(l2); 
LinkedList & LinkedList::operator=(const LinkedList &other)
{
	if (this != &other) // check for self-assignment l1 = l1
	{
 	   if (mySize == other.mySize) // both lists have the same size
 	   {
	    // traverse other list and copy the data member from each node 
	    // into the corresponding node in the calling object list	
	        Node *ptr_other, *ptr;
	        ptr_other = other.first;
	        ptr = first;
	        while (ptr_other != 0)
	        {
	            ptr ->data = ptr_other->data;
	            ptr = ptr->next;
	            ptr_other = ptr_other->next;
	        }
	    }
        else 
        {
        // deallocate memory for all nodes in the calling object
        // starting point: the code from the destructor   
         Node *ptr = first;
         while (first != 0)
         {
         	  first = first ->next;
         	  delete ptr;
         	  ptr = first;
         }
	    // construct a new link list for the calling object that 
	    // matches each node in the other list 		   
 	    // starting point = the code from copyConstructor
 	   
 	    }
	}
	return *this;
}

bool LinkedList::empty() const
{
   if (mySize == 0)
     return true;
   else 
     return false;
}

// insert a new item in the list after pos nodes
// Pre-conditions: conditions satisfied at the beginning of a function
//  	pos has a valid value
// Post-condition = a new node with newItem data stored in the node at pos
void LinkedList::insert(ElementType newItem, int pos)
{
    assert ((pos >= 0) && (pos <= mySize));
    Node *ptrNew, *ptr, *ptrPred;
    // insert in an empty list	or at the beginning of a list
    if (pos == 0)
    {
        //  allocate memory for the new node
        ptrNew = new Node;
        // initialize data field of the new node with new value
        ptrNew->data = newItem;
        //  connect new node to the previous first node in the list
        ptrNew->next = first;
        // make first point to the new Node
        first = ptrNew;
    }
    else // insert somewhere in the middle of the list
    {
        // 1. create a new node
        ptrNew = new Node;
        // 2. copy newItem value in data of the new node
        ptrNew->data = newItem;
        // traverse the list until node at pos-1
        // 3. make ptr point to the first node in the list
        ptr = first;
        ptrPred = first;
        // 4. traverse the list until ptr points to node
        // at pos-1
        for (int i = 0; i < pos; i++)
        {
            ptrPred = ptr;
            ptr = ptr->next;
        }
        // 5. connect new node to node at pos
        ptrNew->next = ptr;
        // 6. connect node at pos-1 to new node
        ptrPred->next = ptrNew;
    }
    mySize++;	
    
}

void LinkedList::display() const
{
    Node *ptr = first;
     while (ptr != 0)
     {
        cout << ptr->data << ' '; 
        ptr = ptr->next;
     }
     cout << endl;
}

/*----------------------------------------------------------------------
     Remove a value from the list at a given position.

     Precondition:  The list is not empty and the position satisfies
         0 <= pos < mySize.
     Postcondition: element at the position determined by pos has been
         removed (provided pos is a legal position).
   ----------------------------------------------------------------------*/

void LinkedList::erase(int pos)
{
     assert(pos >=0 && pos <mySize);
     
     // cannot erase a node in am empty list
     if (mySize == 0)
        cout << "Empty list - nothing to erase " << endl;
     else
     {
      // erase the first node in the list ?
      if (pos == 0)
      {
     	   Node *ptr = first;
     	   
     	   // change first to point to the second node in the list
    		first = ptr->next; 	   
     	   // deallocate memory for the node pointed by ptr (first node)
     		delete ptr;    
      }
      else // erase somewhere in the list except at the beginnig
      {
         
          Node *ptr; // pointer to the node you want to delete
          // the node at pos
          Node *pred; // pointer to the node at pos-1
          // the node before the one you delete
 		  
          ptr  = first;
          pred = first;
          // traverse the list until ptr points to the node you want to delete
          for (int i = 0; i < pos; i++)
          {
          	// update pred = with the value of ptr 
          	pred = ptr;
          	// advance ptr to the next node
            ptr = ptr->next;
          }
          
          // (1) link the predecessor node to the node after the
          // one you delete
          pred->next =  ptr->next; 
          
         // (2) deallocate dynamic memory for the node at pos which is pointed
         //     by ptr
         
         delete ptr;  
      }

      mySize--;
      }
}


int LinkedList::find(ElementType val)
{
     Node *ptr = first;
     int i=0;
	 while (ptr != 0 && ptr->data != val )
     {
      ptr=ptr->next;
	  i++;
     }
	 if(i<mySize)
	 return i;
     else
     return -1;
}

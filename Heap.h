#pragma once

#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

class HeapException: public logic_error
{
public:
   HeapException(const string & message = "")
                        : logic_error(message.c_str())
   { }
};  // end HeapException


template <class T, class CompareType = greater<typename vector<T>::value_type> >
class Heap
{
public:
   Heap();  // default constructor
   // copy constructor and destructor are
   // supplied by the compiler

// Heap operations:
   virtual bool empty() const;
   // Determines whether a heap is empty.
   // Precondition: None.
   // Postcondition: Returns true if the heap is empty;
   // otherwise returns false.

   virtual void heapInsert(const T& newItem);
   // Inserts an item into a heap.
   // Precondition: newItem is the item to be inserted.
   // Postcondition: If the heap was not full, newItem is
   // in its proper position; otherwise HeapException is
   // thrown.

   virtual void heapDelete(T& rootItem);
   // Retrieves and deletes the item in the root of a heap.
   // This item has the largest search key in the heap.
   // Precondition: None.
   // Postcondition: If the heap was not empty, rootItem 
   // is the retrieved item, the item is deleted from the
   // heap. However, if the heap is empty, removal is
   // impossible and the function throws HeapException.

   virtual void pop();
   //removes top element

   virtual T top();
   //gets top element without deleting it.

protected:
   void heapRebuild(int root);
   // Converts the semiheap rooted at index root 
   // into a heap.

private:
   vector<T> items;  // array of heap items
   CompareType Compare;
};  // end class
// End of header file.

template <class T, class CompareType>
Heap<T, CompareType>::Heap()
{
}  // end default constructor

template <class T, class CompareType>
bool Heap<T, CompareType>::empty() const
{
   return bool(items.size() == 0);
}  // end empty

template <class T, class CompareType>
void Heap<T, CompareType>::heapInsert(const T& newItem)
// Method: Inserts the new item after the last item in the
// heap and trickles it up to its proper position. The
// heap is full when it contains MAX_HEAP items.
{
   // place the new item at the end of the heap
   items.push_back(newItem);

   // trickle new item up to its proper position
   int place = items.size()-1;
   int parent = (place - 1)/2;
   while ( (parent >= 0) &&
           Compare(items[place], items[parent]) )
   {  // swap items[place] and items[parent]
      T temp = items[parent];
      items[parent] = items[place];
      items[place] = temp;

      place = parent;
      parent = (place - 1)/2;
   }  // end while
}  // end heapInsert

template <class T, class CompareType>
void Heap<T, CompareType>::heapDelete(T& rootItem)
// Method: Swaps the last item in the heap with the root
// and trickles it down to its proper position.
{
   if (empty())
      throw HeapException("HeapException: Heap empty");
   else
   {  rootItem = items.front();
      items.front() = items.back();
	  items.pop_back();
      heapRebuild(0);
   }  // end if
}  // end heapDelete

template <class T, class CompareType>
void Heap<T, CompareType>::pop()
{
	T rootItem;
	heapDelete(rootItem);
}

template <class T, class CompareType>
T	Heap<T, CompareType>::top()
{
	return items.front();
}



template <class T, class CompareType>
void Heap<T, CompareType>::heapRebuild(int root)
{
   // if the root is not a leaf and the root's search key 
   // is less than the larger of the search keys in the 
   // root's children
   int child = 2 * root + 1;  // index of root's left 
                              // child, if any
   if ( child < items.size() )
   {  // root is not a leaf, so it has a left child at child
      int rightChild = child + 1;  // index of right child, 
                                   // if any

      // if root has a right child, find larger child
      if ( (rightChild < items.size()) &&
           Compare(items[rightChild], items[child]) )
         child = rightChild;  // index of larger child

      // if the root's value is smaller than the
      // value in the larger child, swap values
      if ( Compare(items[child],items[root]) )
      {  T temp = items[root];
         items[root] = items[child];
         items[child] = temp;

         // transform the new subtree into a heap
         heapRebuild(child);
      }  // end if
   }  // end if

   // if root is a leaf, do nothing
}  // end heapRebuild
// End of implementation file.

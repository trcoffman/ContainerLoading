#pragma once

#include "Heap.h"

template <class T, class CompareType = greater<typename vector<T>::value_type> >
class PriorityQueue
{
	Heap<T, CompareType> heap;
public:
	PriorityQueue();
	
	//determines whether the priority queue is empty
	bool empty();

	void push(const T& newItem);
	void pop();
	T   top();
};

template <class T, class CompareType>
PriorityQueue<T, CompareType>::PriorityQueue()
{
}

template <class T, class CompareType>
bool PriorityQueue<T, CompareType>::empty()
{
	return heap.empty();
}

template <class T, class CompareType>
void PriorityQueue<T, CompareType>::push(const T& newItem)
{
	heap.heapInsert(newItem);
}

template <class T, class CompareType>
void PriorityQueue<T, CompareType>::pop()
{
	T item;
	heap.heapDelete(item);
}

template <class T, class CompareType>
T PriorityQueue<T, CompareType>::top()
{
	return heap.top();
}
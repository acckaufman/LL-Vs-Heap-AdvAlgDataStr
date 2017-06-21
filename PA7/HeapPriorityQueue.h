//Amanda Kaufman
//CISS350
//Programming Assignment 7
//HeapPriorityQueue class
//This class, adapted from Programming Assignment 3, implements a priority queue as a heap. 
//Here it is made into a template class.

#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstddef>	//For NULL
#include <new>		//For bad_alloc
using namespace std;

//Exception class for when a client attempts to push an element onto a full queue
class FullQueue {};

//Exception class for when a client attempts to pop an element off an empty queue
class EmptyQueue {};

//Node structure for queue
template <class ItemType>
struct QueNode
{
	ItemType info;
	QueNode *next;
};

//Structure for the heap type
template <class ItemType>
struct HeapType
{
	//Swaps two nodes in the elements array.
	void Swap(ItemType item1, ItemType item2)
	{
		int tempIndex;

		//Search for first element in the array and store its index.
		for (int index = 0; index < numElements; index++)
		{
			if (elements[index] == item1)
			{
				tempIndex = index;
			}
		}

		//Search for second element in the array and swap it with first element.
		for (int count = 0; count < numElements; count++)
		{
			if (elements[count] == item2)
			{
				elements[tempIndex] = item2;
				elements[count] = item1;
			}
		}
	}

	//Post: Heap property of root element is restored.
	void reheapDown(int root, int bottom, int &accumulator)
	{
		int minChild;
		int rightChild;
		int leftChild;

		leftChild = root * 2 + 1;
		rightChild = root * 2 + 2;

		if (leftChild <= bottom)	//If the node is not a leaf
		{
			if (leftChild == bottom)	//If the node only has a left child
				minChild = leftChild;	//assign the value in the left child to minChild.
			else
			{
				if (elements[leftChild] >= elements[rightChild])	//Otherwise, compare
					minChild = rightChild;							//left and right child nodes.
				else
					minChild = leftChild;
			}
			if (elements[root] > elements[minChild])	//If the root element is greater than the child,
			{											//swap the two.
				accumulator++;							//Increment the accumulator for the swap.
				Swap(elements[root], elements[minChild]);
				reheapDown(minChild, bottom, accumulator);	//Recursive call to reheapDown.
			}
		}
	}

	//Post: Heap property of a leaf node is restored.
	void reheapUp(int root, int bottom, int &accumulator)
	{
		int parent;

		if (bottom > root)		//If there is more than one node
		{
			parent = (bottom - 1) / 2;	//Find the parent of the node in question.
			if (elements[parent] > elements[bottom])	//If the value in parent is greater than
			{											//the value in the node, swap the two.
				accumulator++;							//Increment the accumulator for the swap.
				Swap(elements[parent], elements[bottom]);	//Increment the accumulator for the swap.
				reheapUp(root, parent, accumulator);		//Recursive call to reheapUp.
			}
		}
	}

	ItemType *elements;
	int numElements;
};

//Queue implemented as a linked list.
template <class ItemType>
class HeapPriorityQueue
{
private:
	int length;
	HeapType<ItemType> items;
	int maxItems;
	int accumulator;	//Number of elements accessed
public:
	//Function: Class constructor.
	//Post: Maximum number of items is established.  Heap is created.  
	//      Accumulator is set to 0.
	HeapPriorityQueue(int num)
	{
		maxItems = num;
		items.elements = new ItemType[num];
		items.numElements = 0;
		length = 0;
		accumulator = 0;
	}

	//Function: Empty the queue.
	//Post: Queue is empty; all elements have been deallocated.
	void makeEmpty()
	{
		length = 0;
		accumulator = 0;
	}

	//Function: Class destructor.
	//Post: Queue is empty; all elements have been deallocated.
	~HeapPriorityQueue()
	{
		delete[] items.elements;
	}

	//Function: Manually sets accumulator.
	void setAccumulator(int num)
	{
		accumulator = num;
	}

	//Function: Returns value stored in accumulator.
	int getAccumulator() const
	{
		return accumulator;
	}

	//Function: Display all the items in the heap in priority order.
	void displayHeap() const
	{
		cout << "Current Heap:" << endl << endl;
		if (items.numElements == 0)
			cout << "There are currently no items in the heap." << endl << endl;
		else
		{
			for (int index = 0; index < items.numElements; index++)
			{
				cout << items.elements[index] << endl;
			}
			cout << endl;
		}
	}

	//Function: Observe an item in the list, without removing the item.
	//Post: A copy of the item at position index in the list is returned.
	ItemType getItem(int index)
	{
		return elements[index];
	}

	//Function: Adds a new item to the rear of the queue.
	//Pre: Queue has been initialized.
	//Post: If (queue is not full), newItem is at the rear of the queue; otherwise,
	//a FullQueue exception is thrown.
	void enqueue(ItemType newItem)
	{
		if (length == maxItems)
			throw FullQueue();
		else
		{
			length++;
			items.numElements++;
			items.elements[length - 1] = newItem;
			items.reheapUp(0, length - 1, accumulator);
		}
	}

	//Function: Removes front item from the list and returns it in a reference variable.
	//Pre: Queue has been initialized.
	//Post: If (queue is not empty), the front of the queue has been removed and a copy returned,
	//otherwise, an EmptyQueue exception is thrown.
	void dequeue(ItemType &item)
	{
		if (length == 0)
			throw EmptyQueue();
		else
		{
			item = items.elements[0];
			items.elements[0] = items.elements[length - 1];
			length--;
			items.numElements--;
			items.reheapDown(0, length - 1, accumulator);
		}
	}

	//Function: Determine whether or not the queue is empty.
	//Post: Returns true if there are no elements on the queue and false otherwise.
	bool isEmpty() const
	{
		return (length == 0);
	}

	//Function: Determine whether or not the queue is full.
	//Post: Returns true if there is no room for another QueNode object on the free store,
	//and false otherwise.
	bool isFull() const
	{
		return (length == maxItems);
	}
};


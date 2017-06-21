//Amanda Kaufman
//CISS 350
//Programming Assignment 7
//This main() function serves as a test driver to compare the heap and linked list implementations
//of a priority queue where smallest key values take priority.
//These implementations are built into the classes HeapPriorityQueue and ListPriorityQueue.

#include <iostream>
#include "HeapPriorityQueue.h"
#include "ListPriorityQueue.h"
using namespace std;

const int NUM_TEST_ITEMS = 50;

int main()
{
	//###############################################################################
	//Setup																			#
	//###############################################################################

	//Create a bank of 50 test items, stored in an array.
	int testData[NUM_TEST_ITEMS] = { 32, 35, 75, 48, 71, 28, 19, 4, 94, 24,
									 37, 43, 22, 36, 25, 76, 52, 27, 96, 21,
									 73, 1, 44, 82, 29, 20, 34, 18, 9, 31,
									 7, 89, 16, 10, 98, 78, 33, 83, 61, 87,
									 41, 100, 63, 84, 56, 68, 11, 57, 65, 46 };

	//Create variables to store the amount of nodes accessed during each operation.
	int heapEnqueueData;
	int heapDequeueData;
	int listEnqueueData;
	int listDequeueData;

	cout << "Priority Queue: Heap vs. Linked List Comparison" << endl << endl;

	//###############################################################################
	//Heap Implementation Enqueue													#
	//###############################################################################

	//Header
	cout << "--------------------- Step 1: Enqueue Items: Heap ---------------------";
	cout << endl << endl;

	system("pause");
	cout << endl;

	//Create an instance of a heap priority queue.
	HeapPriorityQueue<int> heap(NUM_TEST_ITEMS);

	//Enqueue the items into the heap.
	for (int index = 0; index < NUM_TEST_ITEMS; index++)
		heap.enqueue(testData[index]);

	//Display the current heap.
	heap.displayHeap();

	//Display the number of elements accessed.
	cout << "Number of elements accessed in the heap enqueue operation is: "
		<< heap.getAccumulator() << "." << endl << endl;

	//Store the number of elements accessed.
	heapEnqueueData = heap.getAccumulator();

	system("pause");
	cout << endl;

	//###############################################################################
	//Heap Implementation Dequeue													#
	//###############################################################################

	//Header
	cout << "--------------------- Step 2: Dequeue Items: Heap ---------------------";
	cout << endl << endl;

	system("pause");
	cout << endl;

	//Create a garbage variable for dequeueing items.
	int garbage;

	//Reset the accumulator to 0.
	heap.setAccumulator(0);

	//DEBUGGING:
	//cout << "Debugging: Accumulator is: " << heap.getAccumulator() << endl << endl;

	//Dequeue items from the heap and throw them out.
	for (int index = 0; index < NUM_TEST_ITEMS; index++)
		heap.dequeue(garbage);

	//Display the current heap (should appear empty).
	heap.displayHeap();

	//Display the number of elements accessed.
	cout << "Number of elements accessed in the heap dequeue operation is: "
		<< heap.getAccumulator() << "." << endl << endl;

	//Store the number of elements accessed.
	heapDequeueData = heap.getAccumulator();

	system("pause");
	cout << endl;

	//###############################################################################
	//Linked List Implementation Enqueue											#
	//###############################################################################

	//Header
	cout << "--------------------- Step 3: Enqueue Items: Linked List ---------------------";
	cout << endl << endl;

	system("pause");
	cout << endl;

	//Create an instance of a linked list priority queue.
	ListPriorityQueue<int> list;

	//Add the test items into the linked list in sorted order.
	for (int index = 0; index < NUM_TEST_ITEMS; index++)
		list.putItem(testData[index]);

	//Display the current list.
	list.displayList();

	//Display the number of elements accessed.
	cout << "Number of elements accessed in the list enqueue operation is: "
		<< list.getAccumulator() << "." << endl << endl;

	//Store the number of elements accessed.
	listEnqueueData = list.getAccumulator();

	system("pause");
	cout << endl;

	//###############################################################################
	//Linked List Implementation Dequeue											#
	//###############################################################################

	//Header
	cout << "--------------------- Step 4: Dequeue Items: Linked List ---------------------";
	cout << endl << endl;

	system("pause");
	cout << endl;

	//Reset the accumulator to 0.
	list.setAccumulator(0);

	//DEBUGGING:
	//cout << "Debugging: Accumulator is: " << list.getAccumulator() << endl << endl;

	//Dequeue items from the heap and throw them out.
	for (int index = 0; index < NUM_TEST_ITEMS; index++)
		list.deleteItem(testData[index]);

	//Display the current list (should appear empty).
	list.displayList();

	//Display the number of elements accessed.
	cout << "Number of elements accessed in the list dequeue operation is: "
		<< list.getAccumulator() << "." << endl << endl;

	//Store the number of elements accessed.
	listDequeueData = list.getAccumulator();

	system("pause");
	cout << endl;

	//###############################################################################
	//Results Summary																#
	//###############################################################################

	//Header
	cout << "------------------------------- Results Summary -------------------------------";
	cout << endl << endl;

	cout << "Number of nodes accessed during..." << endl << endl;
	cout << "\tHeap Enqueue: " << heapEnqueueData << endl
		<< "\tHeap Dequeue: " << heapDequeueData << endl
		<< "\tList Enqueue: " << listEnqueueData << endl
		<< "\tList Dequeue: " << listDequeueData << endl << endl;
	cout << "Total nodes accessed during heap operations: " << (heapEnqueueData + heapDequeueData) << endl;
	cout << "Total nodes accessed during list operations: " << (listEnqueueData + listDequeueData) << endl << endl;

	system("pause");
	return 0;
}
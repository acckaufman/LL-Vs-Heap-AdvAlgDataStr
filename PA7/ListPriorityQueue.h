//Amanda Kaufman
//Programming Assignment 7
//CISS 350
//ListPriorityQueue class
//This class implements a sorted linked list, in which smallest items are at the front of the
//list (ascending order).  Here it is made into a template class.

#pragma once
#include <new>	//Needed to catch bad_alloc exception

//Define the NodeType structure for use in this list.
template <class ItemType>
struct NodeType
{
	ItemType info;
	NodeType* next;
};

template <class ItemType>
class ListPriorityQueue
{
private:
	NodeType<ItemType>* listData;
	int length;
	NodeType<ItemType>* currentPos;
	int accumulator;		//Accumulator for number of elements accessed
public:
	//Constructor initializes the length of the list and the head pointer.
	ListPriorityQueue()
	{
		length = 0;
		accumulator = 0;
		listData = nullptr;
	}

	//Destructor makes the list empty, freeing up memory for other applications.
	~ListPriorityQueue()
	{
		makeEmpty();
	}

	//Empties the list and deallocates all items.
	void makeEmpty()
	{
		NodeType<ItemType> *tempPtr;

		while (listData != nullptr)
		{
			tempPtr = listData;
			listData = listData->next;
			delete tempPtr;
		}

		length = 0;
	}

	//Returns true if there is no room for another node on the free store; false otherwise.
	bool isFull() const
	{
		NodeType *location;

		try
		{
			location = new NodeType;
			delete location;
			return false;
		}
		catch (std::bad_alloc exception)
		{
			return true;
		}
	}

	//Returns the current value in the accumulator.
	int getAccumulator() const
	{
		return accumulator;
	}

	//Manually sets the accumulator.
	void setAccumulator(int num)
	{
		accumulator = num;
	}

	//Returns the number of items in the list.
	int getLength() const
	{
		return length;
	}

	//Returns currentPos
	NodeType<ItemType>* getCurrentPos() const
	{
		return currentPos;
	}

	//If the object passed as a parameter matches an object in the list, matching item is returned.
	//Otherwise, object passed as a parameter is returned.
	//Note: This function assumes that the object passed to the function has been initialized.
	ItemType getItem(ItemType item, bool& found)
	{
		bool moreToSearch;
		NodeType *location;

		location = listData;
		found = false;
		moreToSearch = (location != NULL);

		if (item == location->info)
		{
			found = true;
			item = location->info;
		}
		else
		{
			location = location->next;
			moreToSearch = (location != NULL);
		}

		return item;
	}

	//Inserts an item into the list and increments the list length.
	void putItem(ItemType item)
	{
		NodeType<ItemType> *newNode;			//Pointer to node being inserted
		NodeType<ItemType> *predLoc;			//Trailing pointer
		NodeType<ItemType> *location;			//Traveling pointer
		bool moreToSearch;			//Flag for items left to be searched

		location = listData;
		predLoc = NULL;
		moreToSearch = (location != NULL);

		//Find insertion point.
		while (moreToSearch)
		{
			accumulator++;	//Increment accumulator for current node being analyzed.

			if (item > location->info)
			{
				predLoc = location;
				location = location->next;
				moreToSearch = (location != NULL);
			}
			else
			{
				moreToSearch = false;
			}
		}

		//Prepare node for insertion.
		newNode = new NodeType<ItemType>;
		newNode->info = item;

		//Insert node into list.
		if (predLoc == NULL)	//Insert as first list item.
		{
			newNode->next = listData;
			listData = newNode;
		}
		else
		{
			newNode->next = location;
			predLoc->next = newNode;
		}

		length++;
	}

	//Deletes a node from the list.
	//Note: this function assumes that the object passed as a parameter exists in the list,
	//based on a matching key.  It also assumes the object passed as a parameter was initialized.
	void deleteItem(ItemType item)
	{
		NodeType<ItemType> *location = listData;
		NodeType<ItemType> *tempLocation;
		accumulator++;		//Add one to accumulator for listData (head of list).

		//Locate node to be deleted.
		//If the first node matches the parameter, delete the first node.
		if (item == listData->info)
		{
			tempLocation = location;
			listData = listData->next;
		}
		//Otherwise, search the list for the node and delete it.
		else
		{
			while (item != (location->next)->info)
			{
				location = location->next;
				accumulator++;
			}

			//Once found, delete the node at location->next;
			tempLocation = location->next;	//Store address of the node to be deleted
			accumulator++;					//Add to the accumulator for this node
			location->next = (location->next)->next;	//Move the pointer from the previous node to the one after
		}

		delete tempLocation;	//Delete the node
		length--;	//Decrement the length of the list
	}

	//Function: Display all the items in the list.
	void displayList() const
	{
		cout << "Current List:" << endl << endl;
		if (length == 0)
			cout << "There are currently no items in the list." << endl << endl;
		else
		{
			NodeType<ItemType> *tempPtr;
			tempPtr = listData;

			while (tempPtr != NULL)
			{
				cout << tempPtr->info << endl;
				tempPtr = tempPtr->next;
			}
			cout << endl;
		}
	}

	//Initialize current position at the start of the list.
	void resetList()
	{
		currentPos = NULL;
	}

	//Returns a copy of the next item in the list.
	//When the end of the list is reached, currentPos is reset to the beginning of the list.
	ItemType getNextItem()
	{
		if (currentPos == NULL)		//If currentPos is pointing to the end of the list
			currentPos = listData;	//reset it at the beginning of the list
		else
			currentPos = currentPos->next;	//Otherwise, move currentPos to the next list item
		return currentPos->info;			//Return the information stored in the next list item
	}
};
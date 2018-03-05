////////////////////////////////////////////////////////
// ECE 2574, Homework 4, Steven Diamante
// File name: Queue.cpp
// Description: Implementation file for the ADT Queue
// Date: 11/6/2014

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "Queue.h"
using namespace std;

class QueueException: public logic_error
{
public:
QueueException(const string & message = "")
:logic_error(message)
{}
};

// Constructor: initializes front and back point as the line being empty
bankQueue::bankQueue()
{
	front = NULL;
	back = NULL;
};

// Destructor: deallocate memory that was allocated dynamically
bankQueue::~bankQueue()
{
	while(!isEmpty())
		Dequeue();
};

// Checks if queue is empty
bool bankQueue::isEmpty() const
{
	if(front == NULL && back == NULL)
		return true;
	else
		return false;
};

// Adds QueueItemType to back of queue
void bankQueue::Enqueue(QueueItemType aTime, QueueItemType tTime) 
{
	node *temp = new node;
	temp->arrivalT = aTime;
	temp->transactionT = tTime;
	temp->next = NULL;
	if(temp == NULL)
		throw QueueException("Out of memory");
	else
	{
		if(isEmpty()) // First customer
		{
			front = temp;
			back = temp;
			return;
		}
		else // There are already people in line
		{
			back->next = temp;
			back = temp;
		}
	}
};

// Removes QueueItemType from front of queue
void bankQueue::Dequeue()
{
node *temp = front;
	if(isEmpty())
		throw QueueException("Queue is already empty");
	if(front == back)
	{
		front = NULL;
		back = NULL;
	}
	else
		front = front->next; // front points to next node
free(temp);
};

// Retrieves front of the queue
void bankQueue::getFront(QueueItemType& frontaTime, QueueItemType& fronttTime) 
{
	//if(isEmpty())
		//throw QueueException("Queue is already empty");

	frontaTime = front->arrivalT;
	fronttTime = front->transactionT;
};

//Retrieves back of the queue
void bankQueue::getBack(QueueItemType& backaTime, QueueItemType& backtTime)
{
	backaTime = back->arrivalT;
	backtTime = back->transactionT;
};

// returns size of bankQueue
double bankQueue::getSize()
{
double size = 0;
if(front == NULL)
	return 0;
else if(front == back && front != NULL && back != NULL)
	return 1;
else
{
for(node *cur = front; cur != back; cur = cur-> next)
{
	size++;
}
	return size + 1;
}
};

// Prints Queue
void bankQueue::printQueue()
{
node *cur;
for(cur = front; cur != NULL; cur = cur->next)
	cout << cur->arrivalT << " " << cur->transactionT << "   ";
};

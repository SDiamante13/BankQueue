////////////////////////////////////////////////////////
// ECE 2574, Homework 4, Steven Diamante
// File name: Queue.h
// Description: Header file for the ADT Queue
// Date: 11/6/2014

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

// Here the user can specify a different type;
// your implementation should work for double, float, and int

typedef int QueueItemType;

class bankQueue
{

public:
// Constructor: create a stack that contains a dummy node and stores cities, two pointers: prev and next
bankQueue();
// Destructor: deallocate memory that was allocated dynamically
~bankQueue();
// Checks if queue is empty
bool isEmpty() const;
// Adds QueueItemType to back of queue
void Enqueue(QueueItemType aTime, QueueItemType tTime);
// Removes QueueItemType from front of queue
void Dequeue();
// retrives two times from the front of the line
void getFront(QueueItemType& frontATime, QueueItemType& frontTTime);
// retrives two times from the back of the line
void getBack(QueueItemType& backATime, QueueItemType& backTTime); 
// returns the size of the queue
double getSize();
// prints queue for testing purposes
void printQueue();


private:
struct node
{
	QueueItemType arrivalT;
	QueueItemType transactionT;
	node *next; 
};
node *front;
node *back;

}; // End Queue class

// End header file

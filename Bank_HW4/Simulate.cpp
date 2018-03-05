////////////////////////////////////////////////////////
// ECE 2574, Homework 4, Steven Diamante
// File name: Simulate.cpp
// Description: Implementation file for the ADT EventList
// Date: 11/6/2014

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <stdexcept>
#include <stdlib.h>
#include "Simulate.h"
using namespace std;

// Exception Class

class ListException: public logic_error
{
public:
ListException(const string & message = "")
:logic_error(message)
{}
};

// Make eventlist that processes arrivals and departures

// Constructor: initializes counts, times, flags, and head as NULL
EventList::EventList()
{
	head = NULL;
	customerCount = 0;
	currentTime = 0;
	first = true;
	firstLine = true;
};

// Destructor: deallocate memory that was allocated dynamically
EventList::~EventList()
{
	while(!listEmpty())
		popFront();
};

// Check if the eventList is empty
bool EventList::listEmpty() const
{
	if(head == NULL)
		return true;
	else
		return false;
};

// return the size of the Event List (should never exceed 2)
int EventList::listSize()
{
	int size = 0;
	if(listEmpty())
		return 0;
	else if(head->next == NULL)
		return 1;
	else
		for(customerInfo *cur = head; cur != NULL; cur = cur-> next)
{
	size++;
}
return size;
};

// Push a new event to the front of the Event List
void EventList::pushFront(char ET, int aTime, int tTime)
{
	customerInfo *temp = new customerInfo;
	temp->eventType = ET;
	temp->arrivalTime = aTime;
	temp->transactionTime = tTime;
	temp->next = NULL;
	if(temp == NULL)
		throw ListException("Out of Memory");
	if(listEmpty()) // if eventList is empty
	{
		head = temp;
		head->next = NULL;
		return;
	}
	else
	{
		temp->next = head;
		head = temp;
	}
};

// Push a new event to the back of the list
void EventList::pushBack(char ET, int aTime, int tTime)
{
	customerInfo *temp = new customerInfo;
	temp->eventType = ET;
	temp->arrivalTime = aTime;
	temp->transactionTime = tTime;
	temp->next = NULL;
	if(temp == NULL)
		throw ListException("Out of Memory");
	if(listEmpty())
		head = temp;
	else
	head->next = temp;
};

// Pop the first element in the Event List
void EventList::popFront()
{
	if(listEmpty())
		throw ListException("Event List is empty");
	if(head->next == NULL) // if only one item in eventlist
	{
		customerInfo *temp = head;
		head = NULL;
		free(temp);
	}
	else
	{
	customerInfo *temp = head;
	head = head->next;
	free(temp);
	}
};
// I don't need a getFront function because I have a head pointer on the event list

// For testing purposes
void EventList::printList()
{
	customerInfo *cur;
	for(cur = head; cur != NULL; cur = cur->next)
	{
		cout << cur->eventType << " " << cur->arrivalTime << " " << cur->transactionTime << "    "; 
	}
};

// Only function called from main
// This begins the bank simulation and writes the data to an output file
void EventList::simulate(const char* out)
{
	ofstream outputFile(out); // setting up outputFile
	// Simulation begins
	outputFile << "t = 0:  Simulation begins" << endl;
	// push first customer to eventlist
	pushBack('A', arrivalTimeIn.front(), transTimeIn.front());
	// erase these times from input deque
	arrivalTimeIn.pop_front();
	transTimeIn.pop_front();
	currentTime = head->arrivalTime; // current time is the next event that will occur
	// This 
	while(head != NULL || !bankline.isEmpty())
	{
	if(head->eventType == 'A')
		processArrival(outputFile);
	if(head->eventType == 'D')
		processDeparture(outputFile);
	}
	//------------------------------------------------------------------------
	//------------------------------------------------------------------------
	// Simulation done
	// Now compute statistics

  double avgTimeinBank = 0;
  double sumtotalTime = 0;
  double avgTimeWaiting = 0;
  double sumWaiting = 0;
  double avgLineLength = 0;
  double sumLineLength = 0;

  // Total time in Bank
  for(unsigned int n = 0; n < totalTimes.size(); n++)
  {
	 sumtotalTime += totalTimes[n]; // sum of vector totalTimes
  }
  avgTimeinBank = sumtotalTime / totalTimes.size(); // compute avg time in bank

  // Total time waiting
  for(unsigned int n = 0; n < waitTimes.size(); n++)
  {
	  sumWaiting += waitTimes[n]; // sum of vector waitTimes
  }
  avgTimeWaiting = sumWaiting / waitTimes.size(); // compute avg wait time
  if(avgTimeWaiting < 0)
	  avgTimeWaiting = 0;

  // Line lengths
  for(unsigned int n = 0; n < lineLengths.size(); n++)
  {
	  sumLineLength += lineLengths[n]; // sum of vector lineLengths
  }
  avgLineLength = sumLineLength / lineLengths.size();

  // Send results to output file
  outputFile << endl << "Total number of customers: " << customerCount << endl;
  outputFile.precision(1);
  outputFile << "Average amount of time in the bank: " << fixed << avgTimeinBank << endl;
  outputFile << "Maximum amount of time in the bank: " << fixed << maxtimeInBank << endl;
  outputFile << "Average amount of time waiting: " << fixed << avgTimeWaiting << endl;
  outputFile << "Maximum amount of time waiting: " << fixed << maxwaitT << endl;
  outputFile << "Average length of line: " << fixed << avgLineLength << endl;
  outputFile << "Maximum length of line: " << fixed << maxLine << endl;
};

// If the front of the Event List contains an arrival event
// this function will process, output, and delete
void EventList::processArrival(ofstream& outputFile)
{
	bool atFront = bankline.isEmpty(); // If the line is empty -> the customer is in the front of the line
	bankline.Enqueue(head->arrivalTime, head->transactionTime); // Move customer into queue
	currentTime = head->arrivalTime;
	dTime = currentTime + head->transactionTime; // Departure time for customer
	outputFile << "t = " << currentTime << ":  Arrival event" << endl;
	popFront(); // delete this event from the Event List
	if(!bankline.isEmpty())
		lineLengths.push_back(bankline.getSize());
	if(firstLine) // executes first time so a comparison can be set up
		maxLine = lineLengths.front();
	firstLine = false;
	if(atFront)
	{
		// create a departure event for the customer who just got to front of line
		pushFront('D', dTime, 0); 
	}
	// add another arrival event unless there are already 2 
	// must decide to pushBack or pushFront
	if(!arrivalTimeIn.empty()) // if there are still events to be added
	{
	if(arrivalTimeIn.front() < head->arrivalTime) // if this new event executes before the current event list head
		pushFront('A', arrivalTimeIn.front(), transTimeIn.front());
	else
		pushBack('A', arrivalTimeIn.front(), transTimeIn.front());
	arrivalTimeIn.pop_front(); // clear event from input deque
	transTimeIn.pop_front();
	}
	else
		return;
	currentTime = head->arrivalTime;
};

// Special last arrival event
void EventList::processLastA(ofstream& outputFile)
{
	bankline.Enqueue(head->arrivalTime, head->transactionTime);
	currentTime = head->arrivalTime;
	outputFile << "t = " << currentTime << ":  Arrival event" << endl;
	popFront();
};

// If the front of the Event List contains a departure event
// this function will process, output, and delete it
void EventList::processDeparture(ofstream& outputFile)
{
	// compute stats when customer is ready to leave
	int arrivalT, transT;
	bankline.getFront(arrivalT, transT); // retrives arrival and transaction times from front customer
	waitT = currentTime - transT - arrivalT; // wait Time
	if(first) // only executes first time to compare for max wait time
	maxwaitT = waitT;
	if(!first && maxwaitT < waitT)
		maxwaitT = waitT; // new max wait time
	waitTimes.push_back(waitT); // keep track of customers' wait times
	customerCount++; // counts number of customers
	timeInBank = currentTime - arrivalT; // time customer was in bank
	totalTimes.push_back(timeInBank); // keep track of time in bank
	if(first)
		maxtimeInBank = timeInBank;
	if(!first && maxtimeInBank < timeInBank)
		maxtimeInBank = timeInBank;
	first = false;
	// max length
	if(bankline.getSize() > maxLine)
		maxLine = bankline.getSize();
	currentTime = head->arrivalTime; // this is the customer's departure time
	if(!bankline.isEmpty())
		lineLengths.push_back(bankline.getSize());
	bankline.Dequeue(); // customer leaves bank
	popFront(); // customer departure event is deleted from event list
	outputFile << "t = " << currentTime << ":  Departure event" << endl;
	
	// new customer is in front of line
	// or is there?
	if(bankline.isEmpty() && !arrivalTimeIn.empty()) // this is for an empty bank line that still has customers on the way
	{
		if(head == NULL)
			pushFront('A', arrivalTimeIn.front(), transTimeIn.front());
		if(head->eventType == 'A' && head->arrivalTime > currentTime)
			currentTime = head->arrivalTime; // changes currentTime to when the customer arrives at the bank
	}
	// Retrieve new customer's times
	if(!bankline.isEmpty())
		bankline.getFront(arrivalT, transT);
	else
		return;
	dTime = currentTime + transT; // this is the new customer's departure time
	// push front or push back
	if(head == NULL) // if nothing is in the event list just push it in front
		pushFront('D', dTime, 0);
	else
	{
		if(dTime < head->arrivalTime || head == NULL)
			pushFront('D', dTime, 0); // new Departure Event in Event List
		else
			pushBack('D', dTime, 0);
	}
	// bring another arrival event unless event list is full 
	if(!arrivalTimeIn.empty() || head != NULL)
	{
		if(arrivalTimeIn.empty())
		{
			if(head->eventType == 'A')
				processLastA(outputFile);
		}
	else
		if(listSize() < 2)
		{
			if(arrivalTimeIn.front() < head->arrivalTime)
				pushFront('A', arrivalTimeIn.front(), transTimeIn.front());
			else
				pushBack('A', arrivalTimeIn.front(), transTimeIn.front());
	arrivalTimeIn.pop_front();
	transTimeIn.pop_front();
		}
	}
	else
		return;
	currentTime = head->arrivalTime;
};

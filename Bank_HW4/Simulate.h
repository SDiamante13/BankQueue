////////////////////////////////////////////////////////
// ECE 2574, Homework 4, Steven Diamante
// File name: Simulate.h
// Description: Header file for the ADT EventList
// Date: 11/6/2014

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <stdlib.h>
#include "Queue.h"
using namespace std;


class EventList
{
public:
// Singular Linked list with 3 items and next pointer
struct customerInfo
{
	char eventType; // A or D
	int arrivalTime; // The time the customer enters bank
	int transactionTime; // How long the transaction takes
	customerInfo *next;
};

// double ended queues that hold input file times
deque <int> arrivalTimeIn;
deque <int> transTimeIn;

// Constructor: create a linked Event List that has only a head pointer
EventList();
// Destructor: deallocate memory that was allocated dynamically
~EventList();
bool listEmpty() const;
int listSize();
void pushFront(char ET, int aTime, int tTime);
void pushBack(char ET, int aTime, int tTime);
void popFront();
void printList();
void simulate(const char* out);
void processArrival(ofstream& outputFile);
void processLastA(ofstream& outputFile);
void processDeparture(ofstream& outputFile);

// public variables and objects
bankQueue bankline;
int currentTime;
vector <double> waitTimes;
vector <double> totalTimes;
vector <double> lineLengths;
int customerCount;
double waitT, maxwaitT, timeInBank, maxtimeInBank, maxLine, dTime;

private:
// Using linked list for event list
customerInfo *head;
bool first;
bool firstLine;
}; // End EventList class

// End header file

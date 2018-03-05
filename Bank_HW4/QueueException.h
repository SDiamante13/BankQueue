////////////////////////////////////////////////////////
// ECE 2574, Homework 4, Steven Diamante
// File name: QueueException.h
// Description: Header file for Queue exceptions
// Date: 11/6/2014

#include <stdexcept>
#include <string>
using namespace std;

class QueueException: public logic_error
{
public:
QueueException(const string& message)
{}
};
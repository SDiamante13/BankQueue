////////////////////////////////////////////////////////
// Name: Steven Diamante
// File name:   bank.cpp
// Description: HW4 - bank
// Date:        11/5/2014


#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include "Simulate.h"

using namespace std;

int main(int argc, char* argv[]) {
  ifstream inputFile;
  ofstream outputFile;
  int arrivalTime, transTime;
  EventList curlist;

  //The program should take 3 input parameters.
  if (argc != 3) {
    cerr << "Usage: ./bank input.txt output.txt" << endl;
    return -1;
  }

  // Open the input file and output file.
  inputFile.open(argv[1]);
  if (!inputFile) {
    cerr << "Cannot open input file!!!" << endl;
    return -1;
  }
  
  outputFile.open(argv[2]);
  if (!outputFile) {
    cerr << "Cannot open output file!!!" << endl;
    return -1;
  }

  // Now read in the data from the input file.
  while(!inputFile.eof()) {
    inputFile >> arrivalTime >> transTime;
	// push the input file into two deques
	curlist.arrivalTimeIn.push_back(arrivalTime);
	curlist.transTimeIn.push_back(transTime);
    // test whether file stream fails.
    if (inputFile.fail())
	{
      inputFile.clear();
      inputFile.ignore(1024, '\n');
      continue;
    }

    ////////////////////////////////////////////////////////////
    //
    // Push the data into your data structure below.
    // Now you have 2 types of data for each customer:
	//
    // arrivalTime, transTime
    //
    ///////////////////////////////////////////////////////////
    
    
    
    
    
    ///////////////////////////////////////////////////////////
  } // end of while loop file read

  curlist.simulate(argv[2]);
  inputFile.close();
  outputFile.close();
  return 0;
}



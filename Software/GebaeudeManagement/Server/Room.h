#pragma once
#include <iostream>
#include "ToiletSensor.h"
class Room
{
private:
	// private attributes
	std::string _descr;
	int _numToilets;
	int _numDoors;
	int _numTempSensors;
	ToiletSensor _toiletSensors[3];

public:
	Room(); //default constructor
	Room(std::string descr, int numToilets, int numDoors, int numTempSensors);
	
	void designRoom();

	// Getter
	std::string getDescriptor();
	int getNumToilets();
	int getNumDoors();
	int getNumTempSensors();

	// Setter 
	void setDescriptor(std::string descr);
	void setNumToilets(int numToilets);
	void setNumDoors(int numDoors);
	void setNumTempSensors(int numTempSensors);
};


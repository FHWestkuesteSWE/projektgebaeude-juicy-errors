#pragma once
#include <iostream>
#include <list>
#include "DoorActuator.h"
#include "DoorLockingSensor.h"
#include "TemperatureSensor.h"
#include "Thermostat.h"
#include "ToiletSensor.h"

class Room
{
private:
	// private attributes
	std::string _descr;
	int _numToilets;
	int _numDoors;
	int _numTempSensors;

	double _curTemp;
	std::list<bool> _curDoorStatus;

	Thermostat _thermostat;
	std::list<DoorActuator> _doorActuators;
	TemperatureSensor _temperatureSensors[2];
	ToiletSensor _toiletSensors[3];

	std::list <DoorLockingSensor> _doorLockingSensors[2];

public:
	Room(); //default constructor
	Room(std::string descr, int numToilets, int numDoors, int numTempSensors);
	
	void designRoom();
	void setTemperature(double temp);
	void openCloseDoor(int idx, bool isOpen);

	DoorLockingSensor getDoorLockingSensorByIdx(std::list <DoorLockingSensor> l, int idx);
	//bool getBoolByIdx(std::list <DoorLockingSensor> l, int idx);


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


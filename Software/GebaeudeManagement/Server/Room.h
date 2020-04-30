#pragma once
#include <iostream>
#include <list>
#include "DoorActuator.h"
#include "DoorLockingSensor.h"
#include "TemperatureSensor.h"
#include "Thermostat.h"
#include "ToiletSensor.h"
#include <vector>

class Room
{
private:
	// private attributes
	std::string _descr;
	int _numToilets;
	int _numDoors;
	int _numTempSensors;

	double _curTemp;
	std::vector<bool> _curDoorStatus;

	Thermostat _thermostat;
	std::vector<DoorActuator*> _doorActuators;
	std::vector<TemperatureSensor*> _temperatureSensors;
	std::vector <ToiletSensor*> _toiletSensors;

	std::vector<DoorLockingSensor*> _doorLockingSensors[2]; //vector of array

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


#include "Room.h"
#include "DoorActuator.h"
#include "DoorLockingSensor.h"
#include "TemperatureSensor.h"
#include "Thermostat.h"
#include "ToiletSensor.h"

// Constructor
Room::Room(std::string descr, int numToilets, int numDoors, int numTempSensors)
{
	_descr = descr;
	_numToilets = numToilets;
	_numDoors = numDoors;
	_numTempSensors = numTempSensors;

	designRoom();
}

 // default constructor
Room::Room()
{
	designRoom();
}

void Room::designRoom()
{
	for (int i = 0; i < _numToilets; i++)
	{
		_toiletSensors[i] = ToiletSensor();
	}
	
}

// Getter
std::string Room::getDescriptor() { return _descr; }
int Room::getNumToilets() { return _numToilets; }
int Room::getNumDoors() { return _numDoors; }
int Room::getNumTempSensors() { return _numTempSensors; }

// Setter 
void Room::setDescriptor(std::string descr) { _descr = descr; }
void Room::setNumToilets(int numToilets) { _numToilets = numToilets; }
void Room::setNumDoors(int numDoors) { _numDoors = numDoors; }
void Room::setNumTempSensors(int numTempSensors) { _numTempSensors = numTempSensors; }


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

// design room => create objects for every door, actuator and sensor
void Room::designRoom()
{
	for (int i = 0; i < _numToilets; i++)
	{
		_toiletSensors.push_back(&ToiletSensor());
	}

	for (int i = 0; i < _numDoors; i++)
	{
		//add two Door Locking sensors for every Door (redundancy)
		_doorLockingSensors[0].push_back(&DoorLockingSensor());
		_doorLockingSensors[1].push_back(&DoorLockingSensor()); // redundant sensor
		//add isOpen boolean to every door (default: door is closed)
		_curDoorStatus.push_back(false);
	}

	for (int i = 0; i < _numTempSensors; i++)
	{
		_temperatureSensors.push_back(&TemperatureSensor());
	}

	_thermostat = Thermostat();
	_doorActuators.push_back(&DoorActuator());
}

// set temperature to thermostat and save in _curTemp
void Room::setTemperature(double temp)
{
	_curTemp = temp;
	this->_thermostat.setDoubleValue(temp);
}

//set isOpen val to door with index idx
void Room::openCloseDoor(int idx, bool isOpen)
{
	if (_curDoorStatus.size() > idx)
	{
		_curDoorStatus[idx] = isOpen;
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


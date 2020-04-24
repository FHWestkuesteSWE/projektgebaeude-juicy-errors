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

// design room => create objects for every door, actuator and sensor
void Room::designRoom()
{
	for (int i = 0; i < _numToilets; i++)
	{
		_toiletSensors[i] = ToiletSensor();
	}

	for (int i = 0; i < _numDoors; i++)
	{
		//add two Door Locking sensors for every Door (redundancy)
		_doorLockingSensors[0].push_back(DoorLockingSensor());
		_doorLockingSensors[1].push_back(DoorLockingSensor());
		//add isOpen boolean to every door (default: door is closed)
		_curDoorStatus.push_back(false);
	}

	for (int i = 0; i < _numTempSensors; i++)
	{
		_temperatureSensors[i] = TemperatureSensor();
	}

	_thermostat = Thermostat();
	_doorActuators.push_back(DoorActuator());
}

// Function to get list item by giving index
DoorLockingSensor Room::getDoorLockingSensorByIdx(std::list <DoorLockingSensor> l, int idx)
{
	std::list<DoorLockingSensor>::iterator it = l.begin();
	if (l.size() > idx)
	{		
		std::advance(it, idx); // 'it' points to the element at index 'idx'
	}
	
	return *it;
}

void Room::setTemperature(double temp)
{
	_curTemp = temp;
	this->_thermostat.setDoubleValue(temp);
}

void Room::openCloseDoor(int idx, bool isOpen)
{
	std::list<bool>::iterator it = _curDoorStatus.begin();
	if (_curDoorStatus.size() > idx)
	{
		std::advance(it, idx); // 'it' points to the element at index 'idx'
		*it = isOpen;
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


#include "Room.h"
#include "DoorActuator.h"
#include "DoorLockingSensor.h"
#include "TemperatureSensor.h"
#include "Thermostat.h"
#include "ToiletSensor.h"

//TEST: no
//

Room::~Room() {}
//TEST: no
//
// Constructor
Room::Room(const std::string descr, int numToilets, int numDoors, int numTempSensors, bool hasWindows)
{
	_descr = descr;
	_numToilets = numToilets;
	_numDoors = numDoors;
	_numTempSensors = numTempSensors;
	_hasWindows = hasWindows;
	_curTemp = 20.0; // initialize because of RAII principle
	designRoom();
}


// TEST: correct number of objects are create, false values (neg) of _numToilets, _numDoors, _numTempSensors 
//
// design room => create objects for every door, actuator and sensor
int Room::designRoom()
{
	if (_numDoors < 0)
		return EXIT_FAILURE;
	if (_numToilets < 0)
		return EXIT_FAILURE;
	if (_numTempSensors < 0)
		return EXIT_FAILURE;

	for (int i = 0; i < _numToilets; i++)
	{
		_toiletSensors.push_back(&ToiletSensor());
	}

	for (int i = 0; i < _numDoors; i++)
	{
		//add two Door Locking sensors for every Door (redundancy)
		_doorLockingSensors[0].push_back(&DoorLockingSensor());
		_doorLockingSensors[1].push_back(&DoorLockingSensor()); // redundant sensor
		_doorActuators.push_back(&DoorActuator());
		//add isOpen boolean to every door (default: door is closed)
		_curDoorStatus.push_back(false);
	}

	for (int i = 0; i < _numTempSensors; i++)
	{
		_temperatureSensors.push_back(&TemperatureSensor());
	}

	_thermostat = Thermostat();
	_curWindowStatus = false; // windows closed

	return EXIT_SUCCESS;

}

// TEST: no
//
// set temperature to thermostat and save in _curTemp
void Room::setTemperature(double temp)
{
	_curTemp = temp;
	this->_thermostat.setDoubleValue(temp);
}

// TEST: no

double Room::getTemperature()
{
	if (_temperatureSensors.size() > 0)
	{
		return _temperatureSensors[0]->getTemp(TEMP_MIN, TEMP_MAX, _curTemp);
	}
	return -1.0;
}

// TEST: no

//set isOpen val to door with index idx
void Room::openCloseDoor(int idx, bool isOpen)
{
	if (_curDoorStatus.size() > idx)
	{
		_curDoorStatus[idx] = isOpen;
	}
}

// TEST: no

bool Room::getDoorStatus(int idx)
{
	//only use one sensor (other for checker)
	if (_doorLockingSensors[0].size() > idx)
	{
		return _doorLockingSensors[0][idx]->getDoorStatus();
	}
	return false;
}

// TEST: no
//
bool Room::getToiletStatus(int idx)
{
	if (_toiletSensors.size() > idx)
	{
		return _toiletSensors[idx]->getToiletStatus();
	}
	return false;
}

int Room::openCloseWindow(bool areOpen)
{
	bool atLeastOneDoorOpen = false;
	for (int i = 0; i < this->_numDoors; i++)
	{
		if (_curDoorStatus[i] == true)
		{
			atLeastOneDoorOpen = true;
			break;
		}		
	}
	if (atLeastOneDoorOpen)
	{
		this->_curWindowStatus = areOpen;
		return EXIT_SUCCESS;
	}
	else
		return EXIT_FAILURE;
	
}

// TEST: no
//
// Getter
std::string Room::getDescriptor() { return _descr; }
int Room::getNumToilets() { return _numToilets; }
int Room::getNumDoors() { return _numDoors; }
int Room::getNumTempSensors() { return _numTempSensors; }

int Room::getSizeDoorActuators()
{
	return (int) this->_doorActuators.size();
}

int Room::getSizeTempSensors()
{
	return (int) this->_temperatureSensors.size();
}

int Room::getSizeToiletSensors()
{
	return (int) this->_toiletSensors.size();
}

int Room::getSizeDoorLockingSensors()
{
	return (int) this->_doorLockingSensors[0].size() + this->_doorLockingSensors[1].size();
}

bool Room::getHasWindows()
{
	return this->_hasWindows;
}

bool Room::getWindowStatus()
{
	return this->_curWindowStatus;
}

// TEST: no
//
// Setter 
void Room::setDescriptor(const std::string descr) { _descr = descr; }
void Room::setNumToilets(int numToilets) { _numToilets = numToilets; }
void Room::setNumDoors(int numDoors) { _numDoors = numDoors; }
void Room::setNumTempSensors(int numTempSensors) { _numTempSensors = numTempSensors; }
void Room::setHasWindows(bool hasWindows) { _hasWindows = hasWindows; }
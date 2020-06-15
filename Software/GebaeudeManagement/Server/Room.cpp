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
		_toiletSensors.push_back(new ToiletSensor());
	}

	for (int i = 0; i < _numDoors; i++)
	{
		//add two Door Locking sensors for every Door (redundancy)
		_doorLockingSensors[0].push_back(new DoorLockingSensor());
		_doorLockingSensors[1].push_back(new DoorLockingSensor()); // redundant sensor
		_doorActuators.push_back(new DoorActuator());
	}

	for (int i = 0; i < _numTempSensors; i++)
	{
		_temperatureSensors.push_back(new TemperatureSensor());
	}
	_thermostat = new Thermostat();

	if (_hasWindows) {
		_windows = new WindowSensor();
	}

	return EXIT_SUCCESS;

}


std::string Room::getDescriptor() {
	return _descr;
}


void Room::set_thermostat(double temp) {
	if (_thermostat != NULL) {
		_thermostat->set_thermostat(temp);
	}
}


double Room::get_temperature() {
	if (_temperatureSensors.size() > 0) {
		return _temperatureSensors[0]->getTemp();
	}

	return -1;
}


void Room::operate_door(int door_id, bool door_status) {
	if ((_doorActuators.size() > 0) && (_doorActuators.size() > door_id)) {
		return _doorActuators[door_id]->set_door_actuator(door_status);
	}
}


bool Room::get_door_status(int door_id) {
	if ((_doorLockingSensors[0].size() > 0) && (_doorLockingSensors[0].size() > door_id)) {
		return _doorLockingSensors[0][door_id]->getDoorStatus();
	}

	return false;
}


bool Room::get_toilet_status(int toilet_id) {
	if ((_toiletSensors.size() > 0) && (_toiletSensors.size() > toilet_id)) {
		return _toiletSensors[toilet_id]->getToiletStatus();
	}

	return false;
}


bool Room::get_window_status() {
	if (_windows != NULL) {
		return _windows->getWindowStatus();
	}

	return false;
}




// TEST: no
//
// set temperature to thermostat and save in _curTemp
//void Room::setTemperature(double temp)
//{
//	//_curTemp = temp;
//	this->_thermostat.setDoubleValue(temp);
//}

// TEST: no

//double Room::getTemperature()
//{
//	if (_temperatureSensors.size() > 0)
//	{
//		return _temperatureSensors[0]->getTemp();
//	}
//	return -1.0;
//}

//void Room::print_temperatures() {
//	for (int i = 0; i < _numTempSensors; i++)
//	{
//		//std::cout << "sensor object " << &_temperatureSensors[i] << std::endl;
//		std::cout <<  _temperatureSensors[i]->getTemp() << std::endl;
//	}
//}

// TEST: no
//set isOpen val to door with index idx
//void Room::openCloseDoor(int idx, bool isOpen)
//{
//	if (_curDoorStatus.size() > idx)
//	{
//		_curDoorStatus[idx] = isOpen;
//	}
//}

// TEST: no


//bool Room::getDoorStatus(int idx)
//{
//	//only use one sensor (other for checker)
//	if (_doorLockingSensors[0].size() > idx)
//	{
//		return _doorLockingSensors[0][idx]->getDoorStatus();
//	}
//	return false;
//}

// TEST: no
//
//bool Room::getToiletStatus(int idx)
//{
//	if (_toiletSensors.size() > idx)
//	{
//		return _toiletSensors[idx]->getToiletStatus();
//	}
//	return false;
//}


//int Room::openCloseWindow(bool areOpen)
//{
//	bool atLeastOneDoorOpen = false;
//	for (int i = 0; i < this->_numDoors; i++)
//	{
//		if (_curDoorStatus[i] == true)
//		{
//			atLeastOneDoorOpen = true;
//			break;
//		}		
//	}
//	if (atLeastOneDoorOpen)
//	{
//		this->_curWindowStatus = areOpen;
//		return EXIT_SUCCESS;
//	}
//	else
//		return EXIT_FAILURE;
//	
//}

// TEST: no
//
// Getter
//int Room::getNumToilets() { return _numToilets; }
//int Room::getNumDoors() { return _numDoors; }
//int Room::getNumTempSensors() { return _numTempSensors; }
//
//int Room::getSizeDoorActuators()
//{
//	return (int) this->_doorActuators.size();
//}
//
//int Room::getSizeTempSensors()
//{
//	return (int) this->_temperatureSensors.size();
//}
//
//int Room::getSizeToiletSensors()
//{
//	return (int) this->_toiletSensors.size();
//}
//
//int Room::getSizeDoorLockingSensors()
//{
//	return (int) this->_doorLockingSensors[0].size() + this->_doorLockingSensors[1].size();
//}
//
//bool Room::getHasWindows()
//{
//	return this->_hasWindows;
//}
//
//bool Room::getWindowStatus()
//{
//	return this->_curWindowStatus;
//}

// TEST: no
//
// Setter 
//void Room::setDescriptor(const std::string descr) { _descr = descr; }
//void Room::setNumToilets(int numToilets) { _numToilets = numToilets; }
//void Room::setNumDoors(int numDoors) { _numDoors = numDoors; }
//void Room::setNumTempSensors(int numTempSensors) { _numTempSensors = numTempSensors; }
//void Room::setHasWindows(bool hasWindows) { _hasWindows = hasWindows; }
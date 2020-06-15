#pragma once
#include <iostream>
#include <list>
#include "DoorActuator.h"
#include "DoorLockingSensor.h"
#include "TemperatureSensor.h"
#include "Thermostat.h"
#include "ToiletSensor.h"
#include "WindowSensor.h"
#include <vector>

#define TEMP_MAX 50.0
#define TEMP_MIN 0.0

class Room
{
private:
	// private attributes
	std::string _descr;
	int _numToilets;
	int _numDoors;
	int _numTempSensors;
	bool _hasWindows;

	Thermostat* _thermostat;
	WindowSensor* _windows;
	std::vector<DoorActuator*> _doorActuators;
	std::vector<TemperatureSensor*> _temperatureSensors;
	std::vector <ToiletSensor*> _toiletSensors;
	std::vector<DoorLockingSensor*> _doorLockingSensors[2]; //vector of array

public:
	Room(std::string descr, int numToilets, int numDoors, int numTempSensors, bool hasWindows);
	~Room();

	int designRoom();


	void set_thermostat(double temp);
	double get_temperature();

	void operate_door(int door_id, bool door_status);
	bool get_door_status(int door_id);

	bool get_toilet_status(int toilet_id);

	bool get_window_status();

	//void setThermostat(double temp);
	//double getTemperature();
	//void openCloseDoor(int idx, bool isOpen);
	//bool getDoorStatus(int idx);
	//bool getToiletStatus(int idx);
	//int openCloseWindow(bool areOpen);

	// Getter
	std::string getDescriptor();
	//int getNumToilets();
	//int getNumDoors();
	//int getNumTempSensors();
	//int getSizeDoorActuators();
	//int getSizeTempSensors();
	//int getSizeToiletSensors();
	//int getSizeDoorLockingSensors();
	//bool getHasWindows();
	//bool getWindowStatus();

	// Setter 
	//void setDescriptor(std::string descr);
	//void setNumToilets(int numToilets);
	//void setNumDoors(int numDoors);
	//void setNumTempSensors(int numTempSensors);
	//void setHasWindows(bool hasWindows);

	// DEBUG
	//void print_temperatures();
};


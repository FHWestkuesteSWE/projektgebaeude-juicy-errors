#define _CRT_SECURE_NO_WARNINGS
#include "Building.h"
#include"Room.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>

using namespace std;

int Building::getRandInteger(int min, int max) {
	srand(time(0));
	int r = min + rand() % (max-min);
	//std::cout << r; //debug output
	return r;
}

Building::Building(char port[]) {
	createRooms(_rooms);
}

void Building::createRooms(Room* rooms)
{
	int numToilets, numDoors, numTempSensors;
	string descr;
	

	// Room 1: WC1	
	descr = "WC1";
	numToilets = getRandInteger(0, 3);
	numDoors = 1;
	numTempSensors = getRandInteger(1, 2);

	_rooms[0].setDescriptor(descr);
	_rooms[0].setNumToilets(numToilets);
	_rooms[0].setNumDoors(numDoors);
	_rooms[0].setNumTempSensors(numTempSensors);

	// Room 2: WC2	
	descr = "WC2";
	numToilets = getRandInteger(0, 3);
	numDoors = 1;
	numTempSensors = getRandInteger(1, 2);

	_rooms[1].setDescriptor(descr);
	_rooms[1].setNumToilets(numToilets);
	_rooms[1].setNumDoors(numDoors);
	_rooms[1].setNumTempSensors(numTempSensors);

	// Room 3: living room
	descr = "living room";
	numToilets = 0;
	numDoors = 1;
	numTempSensors = getRandInteger(1, 2);

	_rooms[2].setDescriptor(descr);
	_rooms[2].setNumToilets(numToilets);
	_rooms[2].setNumDoors(numDoors);
	_rooms[2].setNumTempSensors(numTempSensors);

	// Room 4: kitchen
	descr = "kitchen";
	numToilets = 0;
	numDoors = getRandInteger(1, 2);
	numTempSensors = getRandInteger(1, 2);

	_rooms[3].setDescriptor(descr);
	_rooms[3].setNumToilets(numToilets);
	_rooms[3].setNumDoors(numDoors);
	_rooms[3].setNumTempSensors(numTempSensors);

	// Room 5: working space
	descr = "working space";
	numToilets = 0;
	numDoors = 1;
	numTempSensors = getRandInteger(1, 2);

	_rooms[4].setDescriptor(descr);
	_rooms[4].setNumToilets(numToilets);
	_rooms[4].setNumDoors(numDoors);
	_rooms[4].setNumTempSensors(numTempSensors);
	
	// Room 6: bedroom
	descr = "bedroom";
	numToilets = 0;
	numDoors = 1;
	numTempSensors = getRandInteger(1, 2);

	_rooms[5].setDescriptor(descr);
	_rooms[5].setNumToilets(numToilets);
	_rooms[5].setNumDoors(numDoors);
	_rooms[5].setNumTempSensors(numTempSensors);
}
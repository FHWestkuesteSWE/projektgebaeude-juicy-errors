#define _CRT_SECURE_NO_WARNINGS
#include "Building.h"
#include"Room.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>

#define NUM_ROOMS 6

int Building::getRandInteger(int min, int max) {
	srand(time(0));
	int r = min + rand() % (max-min);
	//std::cout << r; //debug output
	return r;
}

Building::Building()
{
	Room rooms[NUM_ROOMS];
	createRooms(rooms);
}

void Building::createRooms(Room* rooms)
{
	int numToilets, numDoors, numTempSensors;
	std::string descr;
	

	// Room 1: WC1	
	descr = "WC1";
	numToilets = getRandInteger(0, 3);
	numDoors = 1;
	numTempSensors = getRandInteger(1, 2);

	rooms[0].setDescriptor(descr);
	rooms[0].setNumToilets(numToilets);
	rooms[0].setNumDoors(numDoors);
	rooms[0].setNumTempSensors(numTempSensors);

	// Room 2: WC2	
	descr = "WC2";
	numToilets = getRandInteger(0, 3);
	numDoors = 1;
	numTempSensors = getRandInteger(1, 2);

	rooms[1].setDescriptor(descr);
	rooms[1].setNumToilets(numToilets);
	rooms[1].setNumDoors(numDoors);
	rooms[1].setNumTempSensors(numTempSensors);

	// Room 3: living room
	descr = "living room";
	numToilets = 0;
	numDoors = 1;
	numTempSensors = getRandInteger(1, 2);

	rooms[2].setDescriptor(descr);
	rooms[2].setNumToilets(numToilets);
	rooms[2].setNumDoors(numDoors);
	rooms[2].setNumTempSensors(numTempSensors);

	// Room 4: kitchen
	descr = "kitchen";
	numToilets = 0;
	numDoors = getRandInteger(1, 2);
	numTempSensors = getRandInteger(1, 2);

	rooms[3].setDescriptor(descr);
	rooms[3].setNumToilets(numToilets);
	rooms[3].setNumDoors(numDoors);
	rooms[3].setNumTempSensors(numTempSensors);

	// Room 5: working space
	descr = "working space";
	numToilets = 0;
	numDoors = 1;
	numTempSensors = getRandInteger(1, 2);

	rooms[4].setDescriptor(descr);
	rooms[4].setNumToilets(numToilets);
	rooms[4].setNumDoors(numDoors);
	rooms[4].setNumTempSensors(numTempSensors);
	
	// Room 6: bedroom
	descr = "bedroom";
	numToilets = 0;
	numDoors = 1;
	numTempSensors = getRandInteger(1, 2);

	rooms[5].setDescriptor(descr);
	rooms[5].setNumToilets(numToilets);
	rooms[5].setNumDoors(numDoors);
	rooms[5].setNumTempSensors(numTempSensors);
}
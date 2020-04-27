#pragma once

#include "Room.h"
#define NUM_ROOMS 6

class Building {
public:
	Building(char port[]);	

private:
	Room _rooms[NUM_ROOMS];
	
	int getRandInteger(int min, int max);
	void createRooms(Room* rooms);
};


#define _CRT_SECURE_NO_WARNINGS
#include "Building.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#define NUM_ROOMS 6

int Building::getRandInteger(int min, int max) {
	int r = min + rand() % (max-min);
	//std::cout << r; //debug output
	return r;
}

Building::Building()
{
	for (size_t i = 0; i < 20; i++)
	{
		getRandInteger(1, 5); //test		
	}
}
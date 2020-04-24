#include "Sensor.h"
#include <stdlib.h>
#include<time.h> 

bool Sensor::getBooleanValue()
{
	srand(time(0));
	int r = rand() % 100;
	if (r > 80)
		bVal = true;
	else
		bVal = false;

	return bVal;
}

double Sensor::getDoubleValue(double fMin, double fMax, double lastValue)
{
	srand(time(0));
	double dev;
	int r = rand() % 100; // random integer between 0..100
	double f = (double)rand() / RAND_MAX; // random value between 0..1

	if(lastValue > 0.0)
	{
		dev = 0.1 * lastValue * f; // deviation between 0..10%

		if (r > 50) 
			fVal = lastValue + dev;
		else
			fVal = lastValue - dev;
	}
	else // no value predefined
	{
		fVal = fMin + f * (fMax - fMin);
	}
	return fVal;
}
#include "Sensor.h"
#include <stdlib.h>
#include<time.h> 

// TEST: no
//
bool Sensor::getBooleanValue()
{
	srand(time(0));
	int r = rand() % 100;
	if (r > 80)
		_bVal = true;
	else
		_bVal = false;

	return _bVal;
}

// TEST: fMax < fMin, is output in range and 10% around lastValue
//
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
			_fVal = lastValue + dev;
		else
			_fVal = lastValue - dev;
	}
	else // no value predefined
	{
		_fVal = fMin + f * (fMax - fMin);
	}
	return _fVal;
}
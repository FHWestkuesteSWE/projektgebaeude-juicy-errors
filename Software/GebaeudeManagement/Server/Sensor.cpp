#include "Sensor.h"


Sensor::Sensor()
{	
}

Sensor::~Sensor()
{
}

// TEST: no
//
void Sensor::setBooleanValue(bool set_value)
{
	_bVal = set_value;
}


// TEST: no
//
void Sensor::setDoubleValue(double set_value)
{
	_dVal = set_value;
}

// TEST: no
//
bool Sensor::getBooleanValue()
{
	return _bVal;
}

// TEST: no
//
double Sensor::getDoubleValue()
{
	return _dVal;
}

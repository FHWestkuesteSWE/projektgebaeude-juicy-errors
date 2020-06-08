#include "Actuator.h"

Actuator::Actuator()
{
}

Actuator::~Actuator()
{
}

void Actuator::setBooleanValue(bool val)
{
	_bVal = val;
}

void Actuator::setDoubleValue(double val)
{
	_fVal = val;
}

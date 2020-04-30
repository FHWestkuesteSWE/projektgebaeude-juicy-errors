#include "TemperatureSensor.h"

//default Constructor
TemperatureSensor::TemperatureSensor() {
}

double TemperatureSensor::getTemp(double fMin, double fMax, double lastValue)
{
	return getDoubleValue(fMin, fMax, lastValue);
}

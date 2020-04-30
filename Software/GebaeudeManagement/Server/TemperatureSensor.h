#pragma once
#include "Sensor.h"
class TemperatureSensor :
	public Sensor
{
public:
	TemperatureSensor();

	double getTemp(double fMin, double fMax, double lastValue);
};


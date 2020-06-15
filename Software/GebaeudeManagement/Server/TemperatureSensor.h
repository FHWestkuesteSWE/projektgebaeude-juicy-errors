#pragma once
#include "Sensor.h"

#define TEMP_MIN		0.0
#define TEMP_MAX		50.0
#define TEMP_DEFAULT	20.0

class TemperatureSensor :
	public Sensor
{
public:
	TemperatureSensor();
	~TemperatureSensor();

	double getTemp();

private:
	void set_random_temp();
};
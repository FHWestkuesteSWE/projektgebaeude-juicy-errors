#pragma once
#include "Sensor.h"
class WindowSensor :
	public Sensor
{
public:
	WindowSensor();

	bool getWindowStatus();
};


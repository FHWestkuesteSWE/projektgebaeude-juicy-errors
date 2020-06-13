#include "WindowSensor.h"

//default Constructor
WindowSensor::WindowSensor() {}

bool WindowSensor::getWindowStatus()
{
	return getBooleanValue();
}
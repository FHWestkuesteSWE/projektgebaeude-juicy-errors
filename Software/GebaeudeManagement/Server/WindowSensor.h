#pragma once
#include "Sensor.h"

class WindowSensor :
	public Sensor
{
public:
	WindowSensor();
	~WindowSensor();

	bool getWindowStatus();

private:
	void set_random_window_status();
};
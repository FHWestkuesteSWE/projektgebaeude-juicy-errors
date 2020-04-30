#pragma once
#include "Sensor.h"
class DoorLockingSensor :
	public Sensor
{
public:
	DoorLockingSensor();

	bool getDoorStatus();
};


#pragma once
#include "Sensor.h"
class DoorLockingSensor :
	public Sensor
{
public:
	DoorLockingSensor();
	~DoorLockingSensor();

	bool getDoorStatus();
};


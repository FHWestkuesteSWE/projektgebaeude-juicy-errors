#pragma once
#include "Actuator.h"
class DoorActuator :
	public Actuator
{
public:
	DoorActuator();
	~DoorActuator();

	void set_door_actuator(bool set_value);
};
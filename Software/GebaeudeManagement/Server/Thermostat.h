#pragma once
#include "Actuator.h"
class Thermostat :
	public Actuator
{
public:
	Thermostat();
	~Thermostat();

	void set_thermostat(double set_value);
};
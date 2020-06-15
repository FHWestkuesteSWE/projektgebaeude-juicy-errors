#include "Thermostat.h"

//default Constructor
Thermostat::Thermostat() {
	this->setDoubleValue(20.0);
}

Thermostat::~Thermostat() {
}

void Thermostat::set_thermostat(double set_value) {
	this->setDoubleValue(set_value);
}
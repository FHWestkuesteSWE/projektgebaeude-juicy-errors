#include "DoorActuator.h"

//default Constructor
DoorActuator::DoorActuator() {
	this->setBooleanValue(false);
}

DoorActuator::~DoorActuator() {
}

void DoorActuator::set_door_actuator(bool set_value) {
	this->setBooleanValue(set_value);
}
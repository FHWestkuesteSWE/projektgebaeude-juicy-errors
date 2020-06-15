#include "DoorLockingSensor.h"

//default Constructor
DoorLockingSensor::DoorLockingSensor() {
}

DoorLockingSensor::~DoorLockingSensor() {
}

bool DoorLockingSensor::getDoorStatus()
{
	return this->get_sensor_value_bool();
}

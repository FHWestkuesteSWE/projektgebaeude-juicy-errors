#include "DoorLockingSensor.h"

//default Constructor
DoorLockingSensor::DoorLockingSensor() {}

bool DoorLockingSensor::getDoorStatus()
{
	return getBooleanValue();
}

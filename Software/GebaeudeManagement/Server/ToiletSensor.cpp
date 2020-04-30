#include "ToiletSensor.h"
#include <stdlib.h>

//default Constructor
ToiletSensor::ToiletSensor(){}

bool ToiletSensor::getToiletStatus()
{
	return getBooleanValue();
}



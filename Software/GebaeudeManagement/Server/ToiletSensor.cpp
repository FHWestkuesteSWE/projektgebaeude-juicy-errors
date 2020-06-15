#include "ToiletSensor.h"
#include <stdlib.h>

//default Constructor
ToiletSensor::ToiletSensor() {
	this->set_sensor_value_bool(false);
}

ToiletSensor::~ToiletSensor() {
}

bool ToiletSensor::getToiletStatus()
{
	this->set_random_toilet_status();
	return this->get_sensor_value_bool();
}

void ToiletSensor::set_random_toilet_status() {
	srand(5);
	int r = rand() % 100;
	if (r > 80) {
		this->set_sensor_value_bool(false);
	}
	else {
		this->set_sensor_value_bool(true);
	}
}
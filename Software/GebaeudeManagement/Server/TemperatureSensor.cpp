#include "TemperatureSensor.h"

//default Constructor
TemperatureSensor::TemperatureSensor() {
	this->set_sensor_value_double(TEMP_DEFAULT);
}


TemperatureSensor::~TemperatureSensor() {
}


double TemperatureSensor::getTemp()
{
	this->set_random_temp();
	return this->get_sensor_value_double();
}


void TemperatureSensor::set_random_temp() {
	double current_value = this->get_sensor_value_double();
	double new_value = 0.0;

	if (current_value < TEMP_MIN) {
		new_value = TEMP_DEFAULT;
	}
	else if (current_value > TEMP_MAX) {
		new_value = TEMP_DEFAULT;
	}
	else {
		srand(5);

		int r = rand() % 100; // random integer between 0..100
		double f = (double)rand() / RAND_MAX; // random value between 0..1

		if (current_value > 0.0) {
			double dev;
			dev = 0.1 * current_value * f; // deviation between 0..10%

			if (r > 50)
				new_value = current_value + dev;
			else
				new_value = current_value - dev;
		}
		else // no value predefined
		{
			new_value = TEMP_MIN + f * (TEMP_MAX - TEMP_MIN);
		}
	}

	this->set_sensor_value_double(new_value);
}
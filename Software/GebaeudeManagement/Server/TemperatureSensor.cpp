#include "TemperatureSensor.h"
#include <iostream>

//default Constructor
TemperatureSensor::TemperatureSensor() {
	this->setDoubleValue(TEMP_DEFAULT);
	std::cout << this->getDoubleValue() << std::endl;
}


TemperatureSensor::~TemperatureSensor() {
}


double TemperatureSensor::getTemp()
{
	//this->set_random_temp();
	//std::cout << "read value " << this->getDoubleValue() << std::endl;
	//return this->getDoubleValue();
	return 21.5;
}


void TemperatureSensor::set_random_temp() {
	double current_value = this->getDoubleValue();
	double new_value = 0.0;

	std::cout << "current value " << current_value << std::endl;

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

	std::cout << "new value " << new_value << std::endl;
	this->setDoubleValue(new_value);
}




//srand(time(0));
//int r = rand() % 100;
//if (r > 80)
//_bVal = true;
//else
//_bVal = false;
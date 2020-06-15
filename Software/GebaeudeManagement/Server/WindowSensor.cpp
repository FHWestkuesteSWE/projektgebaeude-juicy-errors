#include "WindowSensor.h"

//default Constructor
WindowSensor::WindowSensor() {
	this->set_sensor_value_bool(false);
}

WindowSensor::~WindowSensor() {
}

bool WindowSensor::getWindowStatus()
{
	return this->get_sensor_value_bool();
}

void WindowSensor::set_random_window_status() {
	srand(5);
	int r = rand() % 100;
	if (r > 80) {
		this->set_sensor_value_bool(false);
	}
	else {
		this->set_sensor_value_bool(true);
	}
}
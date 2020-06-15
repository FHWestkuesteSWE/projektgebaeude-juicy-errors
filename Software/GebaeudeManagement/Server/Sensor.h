#pragma once
#include <stdlib.h>
#include <iostream>

class Sensor
{
protected:
	Sensor();
	~Sensor();	

	void set_sensor_value_bool(bool set_value);
	bool get_sensor_value_bool();

	void set_sensor_value_double(double set_value);
	double get_sensor_value_double();

private:
	bool sensor_value_bool = false;
	double sensor_value_double = 0.0;
};
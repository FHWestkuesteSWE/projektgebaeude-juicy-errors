#include "Sensor.h"


Sensor::Sensor()
{	
}

Sensor::~Sensor()
{
}


void Sensor::set_sensor_value_bool(bool set_value)
{
	sensor_value_bool = set_value;
}



void Sensor::set_sensor_value_double(double set_value)
{
	sensor_value_double = set_value;
}


bool Sensor::get_sensor_value_bool()
{
	return sensor_value_bool;
}


double Sensor::get_sensor_value_double()
{
	return sensor_value_double;
}
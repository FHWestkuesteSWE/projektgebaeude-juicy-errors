#pragma once
#include "Sensor.h"
class ToiletSensor :
	public Sensor
{
public:
	ToiletSensor();
	~ToiletSensor();

	bool getToiletStatus();

private:
	void set_random_toilet_status(void);
};
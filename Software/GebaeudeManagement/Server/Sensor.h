#pragma once

class Sensor
{
protected:
	Sensor();
	~Sensor();	

	void setBooleanValue(bool set_value);
	bool getBooleanValue();

	void setDoubleValue(double set_value);
	double getDoubleValue();

private:
	bool _bVal = false;
	double _dVal = 0.0;
};


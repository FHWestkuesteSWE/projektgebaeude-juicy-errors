#pragma once

class Sensor
{
public:
	Sensor();
	~Sensor();
private:
	// private attributes
	bool _bVal = 0;
	double _fVal = 0;

public:
	bool getBooleanValue();
	double getDoubleValue(double fMin, double fMax, double lastValue);
};


#pragma once

class Sensor
{
private:
	// private attributes
	bool _bVal;
	double _fVal;

public:
	bool getBooleanValue();
	double getDoubleValue(double fMin, double fMax, double lastValue);
};


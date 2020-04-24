#pragma once
class Sensor
{
private:
	// private attributes
	bool bVal;
	double fVal;

public:
	bool getBooleanValue();
	double getDoubleValue(double fMin, double fMax, double lastValue);
};


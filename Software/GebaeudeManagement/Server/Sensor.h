#pragma once

typedef enum {
	ERR_BAD_QUERY,
	ERR_BAD_ROOM_ID,
	ERR_BAD_SENSOR_TYPE,
	ERR_BAD_SENSOR_ID,
	ERR_BAD_SENSOR_VAL,
} ERR_CODES;

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


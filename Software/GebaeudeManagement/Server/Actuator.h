#pragma once

	class Actuator
	{
	public:
		Actuator();
		~Actuator();
	private:
		// private attributes
		bool _bVal = 0;
		double _fVal = 0;
	public:
		void setBooleanValue(bool val);
		void setDoubleValue(double val);
	};

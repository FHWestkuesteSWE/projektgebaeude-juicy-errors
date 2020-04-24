#pragma once

	class Actuator
	{
	private:
		// private attributes
		bool _bVal;
		double _fVal;
	public:
		void setBooleanValue(bool val);
		void setDoubleValue(double val);
	};

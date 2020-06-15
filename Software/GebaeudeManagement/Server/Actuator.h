#pragma once

	class Actuator
	{
	protected:
		Actuator();
		~Actuator();

		void setBooleanValue(bool val);
		void setDoubleValue(double val);

	private:
		bool _bVal = 0;
		double _dVal = 0;

	};
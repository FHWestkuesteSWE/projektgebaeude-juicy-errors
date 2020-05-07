#include "pch.h"
#include "CppUnitTest.h"
#include "Sensor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestServer
{
	TEST_CLASS(UnitTestServer)
	{
	public:
		
		//Tests for class Sensor:
		TEST_METHOD(TestSensorGetDoubleValueInRange)
		{
			Sensor sensor = Sensor();
			double fMin = 0.0;
			double fMax = 5.0;
			double lastValue = 3.0;
			double val = sensor.getDoubleValue(fMin, fMax, lastValue);

			// return value in 20% range around lastValue
			if (val <= lastValue + 0.1 * lastValue && val >= lastValue - 0.1 * lastValue)
			{
				Assert::IsTrue(true);
			}
			else
				Assert::IsTrue(false);;

		}
	};
}

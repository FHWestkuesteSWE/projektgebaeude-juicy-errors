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

			if (val > fMax || val < fMin)
			{
				Assert::IsTrue(false);
			}
			else
				Assert::IsTrue(true);
		}

		TEST_METHOD(TestSensorGetDoubleValueCorrectDeviation)
		{
			Sensor sensor = Sensor();
			double fMin = 0.0;
			double fMax = 5.0;
			double lastValue = 3.0;
			double val = sensor.getDoubleValue(fMin, fMax, lastValue);


			// return value in 20% range around lastValue
			if (val >= lastValue + 0.1 * lastValue && val <= lastValue - 0.1 * lastValue)
			{
				Assert::IsTrue(false);
			}
			else
				Assert::IsTrue(true);
		}

		TEST_METHOD(TestSensorGetDoubleValueFalseParameters)
		{
			Sensor sensor = Sensor();
			double fMin = 5.0;
			double fMax = 1.0;
			double lastValue = 3.0;
			double val1 = sensor.getDoubleValue(fMin, fMax, lastValue);
			//fMin>fMax
			Assert::AreEqual(-1.0, val1);

			fMin = 1.0;
			fMax = 2.0;
			lastValue = 0.0;
			double val2 = sensor.getDoubleValue(fMin, fMax, lastValue);
			// lastValue < fMin
			Assert::AreEqual(fMin, val2);

			fMin = 1.0;
			fMax = 2.0;
			lastValue = 3.0;
			double val3 = sensor.getDoubleValue(fMin, fMax, lastValue);
			// lastValue > fMin
			Assert::AreEqual(fMax, val3);
		}

	};
}

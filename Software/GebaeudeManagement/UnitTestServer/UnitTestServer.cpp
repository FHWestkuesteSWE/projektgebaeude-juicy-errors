#include "pch.h"
#include "CppUnitTest.h"
#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>

#include "Sensor.h"
#include "Server.h"
#include "FileHandling.h"
#include "Room.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_Server
{
	TEST_CLASS(UnitTest_Sensor)
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


	/*** Tests for File handling ***/
	TEST_CLASS(UnitTest_FileHandling) {
public:

	TEST_CLASS_INITIALIZE(Test_FileHandling_Init) {
		char filename[] = "testing.dat";
		fstream file;

		// Create "testing.dat" and write content to it
		file.open(filename, ios::out | ios::trunc);
		if (file.is_open()) {
			file.write("This is the test file.", 23);
			file.close();
			Logger::WriteMessage("Created test file <testing.dat>");
		}

		// make sure "delete.dat" does not exist 
		std::remove("delete.dat");
		Logger::WriteMessage("Test_FileHandling_Init completed");
	}


	/*** Tests for method writeCSV ***/
	//TEST_METHOD(Test_writeCSV_CreateNewFileIfNotExists) {		

	//}


	/*** Tests for method loadCSV ***/
	TEST_METHOD(Test_loadCSV_FileDoesNotExist) {
		char filename[] = "delete.dat";
		std::vector<std::string> data;

		Assert::AreEqual(loadCSV(filename, data), EXIT_FAILURE);
		Logger::WriteMessage("Test_loadCSV_FileDoesNotExist completed");
	}

	TEST_METHOD(Test_loadCSV_FileIsRead) {
		char filename[] = "testing.dat";
		std::vector<std::string> data;

		Assert::IsFalse(data.size());
		Assert::AreEqual(loadCSV(filename, data), EXIT_SUCCESS);
		Assert::IsTrue(data.size());
		Logger::WriteMessage("Test_loadCSV_FileIsRead completed");
	}
	};

	/*** Tests for Class Room ***/
	TEST_CLASS(UnitTest_Room)
	{
	public:
		TEST_METHOD(Test_designRoom_negNumDoorValue) {
			Room* rp = new Room();
			rp->setNumDoors(1);
			// allowed value
			Assert::AreEqual(EXIT_SUCCESS, rp->designRoom());

			rp->setNumDoors(-1);
			// negative value
			Assert::AreEqual(EXIT_FAILURE, rp->designRoom());
		}

		TEST_METHOD(Test_designRoom_negNumToiletValue) {
			Room* rp = new Room();
			rp->setNumToilets(1);
			// allowed value
			Assert::AreEqual(EXIT_SUCCESS, rp->designRoom());

			rp->setNumToilets(-1);
			// negative value
			Assert::AreEqual(EXIT_FAILURE, rp->designRoom());
		}

		TEST_METHOD(Test_designRoom_negNumTempSensorsValue) {
			Room* rp = new Room();
			rp->setNumTempSensors(1);
			// allowed value
			Assert::AreEqual(EXIT_SUCCESS, rp->designRoom());

			rp->setNumTempSensors(-1);
			// negative value
			Assert::AreEqual(EXIT_FAILURE, rp->designRoom());
		}

		TEST_METHOD(Test_designRoom_correctNumTempSensors) {
			Room* rp = new Room();
			rp->setNumTempSensors(4);
			rp->designRoom();
			Assert::AreEqual(rp->getSizeTempSensors(), 4);			
		}

		TEST_METHOD(Test_designRoom_correctNumToiletSensors) {
			Room* rp = new Room();
			rp->setNumToilets(3);
			rp->designRoom();
			Assert::AreEqual(rp->getSizeToiletSensors(), 3);
		}

		TEST_METHOD(Test_designRoom_correctNumDoorLockingSensors) {
			Room* rp = new Room();
			rp->setNumDoors(3);
			rp->designRoom();
			Assert::AreEqual(rp->getSizeDoorLockingSensors(), 3 * 2);
		}

		TEST_METHOD(Test_designRoom_correctNumDoorActuators) {
			Room* rp = new Room();
			rp->setNumDoors(3);
			rp->designRoom();
			Assert::AreEqual(3, rp->getSizeDoorActuators());
		}

		TEST_METHOD(Test_setWindowStatus_doorsClosed_openCloseWindows)
		{
			Room* rp = new Room();
			rp->setHasWindows(true);

			rp->setNumDoors(3);

			rp->designRoom();

			for (int i = 0; i < 3; i++)
			{
				rp->openCloseDoor(i, false); //close all doors
			}

			//forbitten to open windows if doors closed
			Assert::AreEqual(EXIT_FAILURE, rp->openCloseWindow(true));
		}

		TEST_METHOD(Test_setWindowStatus_atLeastOneDoorOpen_openCloseWindows)
		{
			Room* rp = new Room();
			rp->setHasWindows(true);

			rp->setNumDoors(3);

			rp->designRoom();

			for (int i = 0; i < 3; i++)
			{
				rp->openCloseDoor(i, false); //close all doors
			}
			rp->openCloseDoor(1, true); // open one door

			rp->openCloseWindow(true);
			Assert::AreEqual(true, rp->getWindowStatus());
		}

	};

}


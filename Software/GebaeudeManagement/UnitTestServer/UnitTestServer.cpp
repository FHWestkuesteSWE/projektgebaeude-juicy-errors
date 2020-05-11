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
				file << "This is the original test file." << '\n';
				file.close();
				Logger::WriteMessage("Created test file <testing.dat>");
			}

			// make sure the files for the exist test do not exist yet
			std::remove("truncate.dat");
			std::remove("size.log");

			Logger::WriteMessage("Test_FileHandling_Init completed");
		}


		/*** Tests for method txt_putLine ***/
		TEST_METHOD(Test_txt_putLine_FileDoesNotExist) {
			char filename[] = "deleted.dat";
			std::string line = std::string("File created by txt_putLine.");

			Assert::IsFalse(txt_putLine(filename, line));

			fstream file(filename);
			Assert::IsFalse(file.good());

			Logger::WriteMessage("Test_txt_putLine_FileDoesNotExist completed");
		}

		TEST_METHOD(Test_txt_putLine_FileSizeIncreaseMatchesDataSize) {
			char filename[] = "testing.dat";
			std::string line = std::string("Added by txt_putLine.");

			// determine file size before the operation
			ifstream testFile(filename, ios::binary);
			auto begin = testFile.tellg();
			testFile.seekg(0, ios::end);
			auto end = testFile.tellg();
			auto fsize_start = (end - begin);
			testFile.close();

			Assert::IsTrue(txt_putLine(filename, line));

			// determine file size after the operation
			testFile.open(filename, ios::binary);
			begin = testFile.tellg();
			testFile.seekg(0, ios::end);
			end = testFile.tellg();
			auto fsize_end = (end - begin);
			testFile.close();

			// write data and file size to file size.log
			std::string size;
			size.append("putLine data size: "); size.append(std::to_string(line.size()));
			size.append("\nputLine start file size: "); size.append(std::to_string(fsize_start));
			size.append("\nputLine end file size: "); size.append(std::to_string(fsize_end));
			size.append("\nputLine file size diff: "); size.append(std::to_string(fsize_end - fsize_start));
			fstream log;
			log.open("size.log", ios::out | ios::app);
			log << size << '\n';
			log.close();

			Assert::IsTrue(fsize_end - 1 == fsize_start + line.length() + 1);	// substract 1 from fsize_end due to the newline character, add 1 to line.length() due to string terminator

			Logger::WriteMessage("Test_txt_putLine_FileSizeIncreaseMatchesDataSize completed");
		}


		/*** Tests for method txt_truncate ***/
		TEST_METHOD(Test_txt_truncate_FileDoesNotExistCreatedNew) {
			char filename[] = "truncate.dat";
			std::vector<std::string> data;
			data.push_back("File created by txt_truncate.");

			Assert::IsTrue(txt_truncate(filename, data));

			fstream file(filename);
			Assert::IsTrue(file.good());

			Logger::WriteMessage("Test_txt_truncate_FileDoesNotExistCreatedNew completed");
		}

		TEST_METHOD(Test_txt_truncate_FileSizeIncreaseMatchesDataSize) {
			char filename[] = "truncate.dat";
			std::vector<std::string> data;
			data.push_back("File content overwritten by txt_truncate.");

			Assert::IsTrue(txt_truncate(filename, data));

			// determine file size after the operation
			ifstream testFile(filename, ios::binary);
			auto begin = testFile.tellg();
			testFile.seekg(0, ios::end);
			auto end = testFile.tellg();
			auto fsize = (end - begin);
			testFile.close();
			
			// write truncated file size to file size.log
			std::string size;
			size.append("Truncate data size: "); size.append(std::to_string(data[0].size()));
			size.append("\nTruncate file size: "); size.append(std::to_string(fsize));
			fstream log;
			log.open("size.log", ios::out | ios::app);
			log << size << '\n';
			log.close();

			Assert::IsTrue(data[0].size() + 1 == fsize - 1);	// add 1 to data size due to string terminator, substract fsize by 1 due to newline character

			Logger::WriteMessage("Test_txt_truncate_FileSizeIncreaseMatchesDataSize completed");
		}
	

		/*** Tests for method txt_read ***/
		TEST_METHOD(Test_txt_read_FileDoesNotExist) {
			char filename[] = "deleted.dat";
			std::vector<std::string> data;

			Assert::IsFalse(txt_read(filename, data));

			fstream file(filename);
			Assert::IsFalse(file.good());

			Logger::WriteMessage("Test_txt_read_FileDoesNotExist completed");
		}

		TEST_METHOD(Test_txt_read_OutputVectorSizeIncreased) {
			char filename[] = "testing.dat";
			std::vector<std::string> data;
			int dataSize = 0;

			Assert::IsTrue(data.empty());
			Assert::IsTrue(txt_read(filename, data));

			// determine file size after the operation
			ifstream testFile(filename, ios::binary);
			auto begin = testFile.tellg();
			testFile.seekg(0, ios::end);
			auto end = testFile.tellg();
			auto fsize = (end - begin);
			testFile.close();

			for (int i = 0; i < data.size(); i++) {
				dataSize += data[i].size();
			}

			// write read data size to file size.log
			std::string size;
			size.append("read data size: "); size.append(std::to_string(dataSize));
			size.append("\nread file size: "); size.append(std::to_string(fsize));
			size.append("\nread file lines: "); size.append(std::to_string(data.size()));
			fstream log;
			log.open("size.log", ios::out | ios::app);
			log << size << '\n';
			log.close();

			Assert::IsTrue(dataSize + data.size() == fsize - 1);	// substract fsize by 1 due to newline character

			Logger::WriteMessage("Test_txt_read_FileIsRead completed");
		}



		/*** Tests for method txt_exists ***/
		TEST_METHOD(Test_txt_exists_FileDoesNotExist) {
			char filename[] = "deleted.dat";
			std::vector<std::string> data;

			Assert::IsFalse(txt_exists(filename));

			fstream file(filename);
			Assert::IsFalse(file.good());

			Logger::WriteMessage("Test_txt_exists_FileDoesNotExist completed");
		}

		TEST_METHOD(Test_txt_exists_FileDoesExist) {
			char filename[] = "testing.dat";
			std::vector<std::string> data;

			Assert::IsTrue(txt_exists(filename));

			fstream file(filename);
			Assert::IsTrue(file.good());

			Logger::WriteMessage("Test_txt_exists_FileDoesExist completed");
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


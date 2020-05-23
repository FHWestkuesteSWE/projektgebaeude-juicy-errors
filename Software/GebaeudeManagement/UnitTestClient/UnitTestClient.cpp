#include "pch.h"
#include "CppUnitTest.h"

#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <sys/stat.h> // for file exists
#include <fstream>
#include "main.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestClient
{
  //----------------------------------------------------------------------------
  // askForValue ()
  //----------------------------------------------------------------------------
  TEST_CLASS( UnitTest_askForValue )
  {

  public:

    /* TEST_CLASS_INITIALIZE ( UnitTestInit ) { */
    /*   roomDescriptors.clear(); // clear list */
    /*   roomDescriptors.push_back ("kitchen1"); // fill roomDescriptors list with item */
    /* } */
    
    TEST_METHOD( returnNumber )
    {
      char descr[10] = "kitchen1"; 
      int roomId = 0; 
      roomDescriptors.clear(); // clear list
      roomDescriptors.push_back ("kitchen1"); // fill roomDescriptors list with item

      Assert::AreEqual( 42, askForValue (descr, roomId ) ); // expecting default kb entry for UNITTEST
    }

    TEST_METHOD( descrIsEmpty )
    {
      char descr[2] = ""; 
      int roomId = 0; 
      roomDescriptors.clear(); // clear list
      roomDescriptors.push_back ("kitchen1"); // fill roomDescriptors list with item

      Assert::AreEqual( -1, askForValue (descr, roomId ) ); // expecting -1 for ERROR
    }

    /* does not even compile...
    TEST_METHOD( descrNotZeroTerminated )
    {
      char descr[2]; 
      descr[0] = 'f';
      descr[1] = 'o';
      descr[2] = 'o';
      int roomId = 0; 

      Assert::AreEqual( askForValue (descr, roomId ), -1 ); // expecting -1 for ERROR
    }
    */
    
    TEST_METHOD( roomIdInRange )
    {
      char descr[10] = "kitchen1"; 
      int roomId = 1; // item does not exist
      roomDescriptors.clear(); // clear list
      roomDescriptors.push_back ("kitchen1"); // fill roomDescriptors list with item

      Assert::AreEqual( -1, askForValue (descr, roomId ) ); // expecting -1 for ERROR
    }
  };

  //----------------------------------------------------------------------------
  // lockOrUnlock ()
  //---------------------------------------------------------------------------- 
  TEST_CLASS( UnitTest_lockOrUnlock )
  {

  public:

    TEST_METHOD( descIsEmpty )
    {
      char descr[2] = ""; 
      int roomId = 0; 
      roomDescriptors.clear(); // clear list
      roomDescriptors.push_back ("kitchen1"); // fill roomDescriptors list with item

      Assert::AreEqual( -1, lockOrUnlock (descr, roomId ) ); // expecting -1 for ERROR
    }
    
    TEST_METHOD( roomIdInRange )
    {
      char descr[10] = "kitchen1"; 
      int roomId = 1; // item does not exist
      roomDescriptors.clear(); // clear list
      roomDescriptors.push_back ("kitchen1"); // fill roomDescriptors list with item

      Assert::AreEqual( -1, askForValue (descr, roomId ) ); // expecting -1 for ERROR
    }

  };

  //----------------------------------------------------------------------------
  // selectRoom ()
  //---------------------------------------------------------------------------- 
  TEST_CLASS( UnitTest_selectRoom )
  {

  public:

    TEST_METHOD( roomCountInRange )
    {
      kbRetVal = 42;
      roomDescriptors.clear(); // clear list
      roomDescriptors.push_back ("kitchen1"); // fill roomDescriptors list with item

      Assert::AreEqual( -1, selectRoom () ); // expecting -1 for ERROR
    }
    
    TEST_METHOD( returnsRoomID )
    {
      kbRetVal = 1;
      roomDescriptors.clear(); // clear list
      roomDescriptors.push_back ("kitchen1"); // fill roomDescriptors list with item
      roomDescriptors.push_back ("living1"); // fill roomDescriptors list with item

      Assert::AreEqual( kbRetVal, selectRoom () );
    }

  };

  //----------------------------------------------------------------------------
  // selectSensor ()
  //---------------------------------------------------------------------------- 
  TEST_CLASS( UnitTest_selectSensor )
  {

  public:
    
    TEST_METHOD( roomInRange )
    {
      kbRetValCh = 't';
      int room = 42;
      roomDescriptors.clear(); // clear list
      roomDescriptors.push_back ("kitchen1"); // fill roomDescriptors list with item
      char sens[5];

      Assert::AreEqual( kbRetValCh, selectSensor (room, sens) ); 
    }
    
  };
  
  //----------------------------------------------------------------------------
  // selectAction ()
  //---------------------------------------------------------------------------- 
  TEST_CLASS( UnitTest_selectAction )
  {

  public:
    
    TEST_METHOD( descrIsEmpty )
    {
      char descr[2] = ""; 
      kbRetValCh = 'g';
      roomDescriptors.clear(); // clear list
      roomDescriptors.push_back ("kitchen1"); // fill roomDescriptors list with item

      Assert::AreEqual( 'g', selectAction (descr) ); // expecting keyboard input 
    }

  };
  
  //----------------------------------------------------------------------------
  // writeLog ( filename, message )
  //---------------------------------------------------------------------------- 
  TEST_CLASS( UnitTest_writeLog )
  {

  public:
    
    TEST_METHOD( fileDoesntExist )
    {
      char message[] = "This is a test!";
      char filename[] = "testlogfile.txt";
      struct stat info;

      writeLog ( filename, message ); // file should be created if it doesnt exist

      int ret = stat (filename, &info);

      Assert::AreEqual( 0, ret ); // should return 0 if file exists

      if (!ret) remove(filename); // delete testfile
    }
    
    TEST_METHOD( fileNotWriteable )
    {
      char message[] = "This is a test!";
      char filename[] = "testlogfile.txt";
      
      writeLog (filename, message);

      // open file and check if message was written
      std::ifstream in(filename, std::ios::out); 
      std::string line;
      while (std::getline(in, line)); 
      in.close();
      // ---

      size_t pos = line.find (message); // looking for the position of the test message in line
      Assert::AreNotSame ( 0, (int)pos ); // position is no null
      
      // delete file if it was created
      struct stat info;
      int ret = stat (filename, &info);
      if (!ret) remove(filename); // delete testfile
      // ---
    }

  };
  
}

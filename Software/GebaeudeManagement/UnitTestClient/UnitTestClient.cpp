#include "pch.h"
#include "CppUnitTest.h"

#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <sys/stat.h> // for file exists

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

      Assert::AreEqual( askForValue (descr, roomId ), 42 ); // expecting default kb entry for UNITTEST
    }

    TEST_METHOD( descrIsEmpty )
    {
      char descr[2] = ""; 
      int roomId = 0; 
      roomDescriptors.clear(); // clear list
      roomDescriptors.push_back ("kitchen1"); // fill roomDescriptors list with item

      Assert::AreEqual( askForValue (descr, roomId ), -1 ); // expecting -1 for ERROR
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

      Assert::AreEqual( askForValue (descr, roomId ), -1 ); // expecting -1 for ERROR
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

      Assert::AreEqual( lockOrUnlock (descr, roomId ), -1 ); // expecting -1 for ERROR
    }
    
    TEST_METHOD( roomIdInRange )
    {
      char descr[10] = "kitchen1"; 
      int roomId = 1; // item does not exist
      roomDescriptors.clear(); // clear list
      roomDescriptors.push_back ("kitchen1"); // fill roomDescriptors list with item

      Assert::AreEqual( askForValue (descr, roomId ), -1 ); // expecting -1 for ERROR
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

      Assert::AreEqual( selectRoom (), -1 ); // expecting -1 for ERROR
    }
    
    TEST_METHOD( returnsRoomID )
    {
      kbRetVal = 1;
      roomDescriptors.clear(); // clear list
      roomDescriptors.push_back ("kitchen1"); // fill roomDescriptors list with item
      roomDescriptors.push_back ("living1"); // fill roomDescriptors list with item

      Assert::AreEqual( selectRoom (), kbRetVal );
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

      Assert::AreEqual( selectSensor (room, sens), kbRetValCh ); // expecting -1 for ERROR
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

      Assert::AreEqual( selectAction (descr), 'g' ); // expecting keyboard input 
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

      Assert::AreEqual( ret, 0); // should return 0 if file exists

      if (!ret) DeleteFile(filename); // delete testfile
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

      Assert::AreEqual( message, line ); // expecting keyboard input 
      
      // delete file if it was created
      struct stat info;
      int ret = stat (filename, &info);
      if (!ret) DeleteFile(filename); // delete testfile
      // ---
    }

  };
  
}

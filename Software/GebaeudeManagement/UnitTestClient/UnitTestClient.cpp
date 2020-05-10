#include "pch.h"
#include "CppUnitTest.h"

#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>

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
}

#include "pch.h"
#include "CppUnitTest.h"

#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>

#define UNITTEST

#include "main.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestClient
{
  TEST_CLASS( UnitTest_askForValue )
  {

  public:

    /* TEST_CLASS_INITIALIZE ( UnitTestInit ) */
    
    TEST_METHOD( descrIsEmpty )
    {
      char descr[2] = ""; 
      roomDescriptors.clear(); // clear list
      roomDescriptors.push_back ("kitchen1"); // fill roomDescriptors list with item
      int roomId = 0; 

      Assert::AreEqual( askForValue (descr, roomId ), -1 ); 
    }

    /*
    TEST_METHOD( descrNotZeroTerminated )
    {
      char descr[2]; 
      descr[0] = 'f';
      descr[1] = 'o';
      descr[2] = 'o';
      roomDescriptors.clear(); // clear list
      roomDescriptors.push_back ("kitchen1"); // fill roomDescriptors list with item
      int roomId = 0; 

      Assert::AreEqual( askForValue (descr, roomId ), -1 ); 
    }
    */
    
    
    TEST_METHOD( roomIdInRange )
    {
      char descr[10] = "kitchen1"; 
      roomDescriptors.clear(); // clear list
      roomDescriptors.push_back ("kitchen1"); // fill roomDescriptors list with item
      int roomId = 1; // item does not exist

      Assert::AreEqual( askForValue (descr, roomId ), -1 ); 
    }
  };
}

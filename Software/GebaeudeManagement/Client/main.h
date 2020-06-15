#ifndef INC_MAIN_H
#define INC_MAIN_H

#include <signal.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Client.h"
#include <ctime>

// room descriptors
#define NUM_ROOMS 3

#define FILENAME "client.log"

#define GET_VALUE 1
#define SET_VALUE 2

// extern std::vector<std::string> roomDescriptors; // list of room descriptors from server

extern int kbRetVal; // default integer return value for keyboard entry
extern char kbRetValCh; // default char return value for keyboard entry



int writeLog        ( const char * filename, const char * message );

#endif /* INC_MAIN_H */


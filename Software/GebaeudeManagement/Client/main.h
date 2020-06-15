#ifndef INC_MAIN_H
#define INC_MAIN_H

#include <signal.h>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

#include "Client.h"
#include "AESCryptor.h"

// room descriptors
#define NUM_ROOMS 3

#define FILENAME "client.log"
#define KEYFILE  "aes.key"

#define GET_VALUE 1
#define SET_VALUE 2

// extern std::vector<std::string> roomDescriptors; // list of room descriptors from server



int writeLog        ( const char * filename, const char * message );

#endif /* INC_MAIN_H */


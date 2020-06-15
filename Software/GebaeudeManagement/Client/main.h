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

extern std::vector<std::string> roomDescriptors; // list of room descriptors from server

extern int kbRetVal; // default integer return value for keyboard entry
extern char kbRetValCh; // default char return value for keyboard entry

typedef enum {
	SENSOR_TEMP,
	SENSOR_DOOR,
	SENSOR_TOILET,
	SENSOR_WINDOW,
} SENSOR_TYPES;

//typedef enum {
//	QUERY_GET,
//	QUERY_SET,
//	QUERY_CFG,
//} QUERY_TYPES;

//int askForValue     ( const char * descr, int roomID );
//// int askForValue   ( const char * descr, int roomID, int dim_high, int dim_low );
//char selectAction   ( const char * descr );
//int lockOrUnlock    ( const char * descr, int roomID ); 
int selectRoom      ( void );
//char selectSensor   ( int room, char * sens );

int writeLog        ( const char * filename, const char * message );
int getKBEntry      ( char * kbentry );
int splitString  (const std::string &txt, std::vector<std::string> &strs, char ch);

void print_select_sensor_menu();
void client_send_request(Client* client, char* request, char* answer);

SENSOR_TYPES select_sensor_or_actuator();
int select_query_for_chosen_sensor(int room_number, SENSOR_TYPES sensor_type, Client* client, char* request, char* answer);
int execute_query_temp(int room_number, Client* client, char* request, char* answer);
int execute_query_door(int room_number, Client* client, char* request, char* answer);
int execute_query_toilet(int room_number, Client* client, char* request, char* answer);
int execute_query_window(int room_number, Client* client, char* request, char* answer);

#endif /* INC_MAIN_H */


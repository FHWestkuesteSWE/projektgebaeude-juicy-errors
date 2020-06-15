#pragma once
#include "BasicClient.h"
#include "SSLClient.h"
#include <string>
    
class Client : public SSLClient
{
public: 
   //Client();
  Client(char server[], char port[]);
  // void sendRequest(const char request[], char answer[]);
  ~Client();

  char * getStrReq ( void );
  char * getStrAns ( void );

  int selectRoom      ( void );
  int select_sensor_or_actuator( int room_number );

  int getKBEntry      ( char * kbentry );

protected:
    int kbRetVal; // default integer return value for keyboard entry
    char kbRetValCh; // default char return value for keyboard entry

    std::vector<std::string> roomDescriptors; // list of room descriptors from server

    /* char * request; */
    /* char * answer; */
    char request[1024];
    char answer[1024]; 
 
 private:
  typedef enum {
    SENSOR_TEMP,
    SENSOR_DOOR,
    SENSOR_TOILET,
    SENSOR_WINDOW,
  } SENSOR_TYPES;

  void print_select_sensor_menu();
  int select_query_for_chosen_sensor(int room_number, SENSOR_TYPES sensor_type );
  int execute_query_temp(int room_number);
  int execute_query_door(int room_number);
  int execute_query_toilet(int room_number); 
  int execute_query_window(int room_number);
  void client_send_request ();
  int splitString  (const std::string &txt, std::vector<std::string> &strs, char ch);
  

}; 

#ifndef INC_MAIN_H
#define INC_MAIN_H

// room descriptors
#define NUM_ROOMS 3

#define FILENAME "client.log"

#define GET_VALUE 1
#define SET_VALUE 2

extern std::vector<std::string> roomDescriptors; // list of room descriptors from server

extern int kbRetVal; // default integer return value for keyboard entry
extern char kbRetValCh; // default char return value for keyboard entry

int askForValue     ( const char * descr, int roomID );
// int askForValue   ( const char * descr, int roomID, int dim_high, int dim_low );
char selectAction   ( const char * descr );
int lockOrUnlock    ( const char * descr, int roomID ); 
int selectRoom      ( void );
char selectSensor   ( int room, char * sens );

int writeLog        ( const char * filename, const char * message );
int getKBEntry      ( char * kbentry );
int splitString  (const std::string &txt, std::vector<std::string> &strs, char ch);

void menu_select_sensor_or_actuator(int roomNumber, char req[], char ans[]);
void client_send_request(Client* client, char* request, char* answer);

#endif /* INC_MAIN_H */


#ifndef INC_MAIN_H
#define INC_MAIN_H

// room descriptors
#define NUM_ROOMS 3

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

int writeLog        ( char * filename, char * message );
int getKBEntry      ( char * kbentry );
size_t splitString  (const std::string &txt, std::vector<std::string> &strs, char ch);

#endif /* INC_MAIN_H */


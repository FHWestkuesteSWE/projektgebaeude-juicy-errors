#ifndef INC_MAIN_H
#define INC_MAIN_H

// room descriptors
#define NUM_ROOMS 3

#define GET_VALUE 1
#define SET_VALUE 2

/* const char roomDescriptors[NUM_ROOMS][50] = */ 
/* { */ 
/*   "livingRoom", */
/*   "kitchen", */
/*   "toiletRoom1", */
/* }; */
    
std::vector<std::string> roomDescriptors; // list of room descriptors from server

int askForValue   ( const char * descr, int roomID );
// int askForValue   ( const char * descr, int roomID, int dim_high, int dim_low );
char selectAction  ( const char * descr );
int lockOrUnlock  ( const char * descr, int roomID );
size_t splitString (const std::string &txt, std::vector<std::string> &strs, char ch);

int selectRoom    ( int roomCount );
char selectSensor ( int room, char * sens );

#endif /* INC_MAIN_H */


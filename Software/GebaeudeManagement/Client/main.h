// room descriptors
#define NUM_ROOMS 3

#define GET_VALUE 1
#define SET_VALUE 2

const char roomDescriptors[NUM_ROOMS][50] = 
{ 
  "livingRoom",
  "kitchen",
  "toiletRoom1",
};

int askForValue   ( const char * descr, int roomID, int dim_high, int dim_low );
int whichRoom     (void);
int getOrSet      ( const char * descr );
int lockOrUnlock  ( const char * descr, int roomID );

#pragma once
#include "BasicServer.h"
#include "Room.h"


#define NUM_MAX_ROOMS	255
#define DESCR_MAX_LEN	12
const std::string CONFIG_NAME = "building.cfg";

typedef enum {
	ERR_BAD_QUERY,
	ERR_BAD_ROOM_ID,
	ERR_BAD_SENSOR_TYPE,
	ERR_BAD_SENSOR_ID,
	ERR_BAD_SENSOR_VAL,
} ERR_CODES;

typedef enum {
	SENSOR_TEMP,
	SENSOR_DOOR,
	SENSOR_TOILET,
} SENSOR_TYPES;


class Server : public BasicServer {
public:	
	Server();
	~Server();
	void start(char port[]);
	
protected:
	void processRequest(char request[], char answer[]);
	
private:
	int build();
	int loadCFG();
	int writeCFG();
	void properties(char* out);
	Room* createRoom(std::string roomProps);
	int addRoom(std::string roomProps);
	int deleteRoom(int idx);
	void print(std::string msg);

	std::vector<Room*> _rooms;
	std::vector<std::string> roomCFG;
};


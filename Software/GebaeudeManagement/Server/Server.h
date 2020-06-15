#pragma once

#include "BasicServer.h"
#include "Room.h"


#define NUM_MAX_ROOMS	255
#define DESCR_MAX_LEN	12
const char CONFIG_NAME[] = "building.cfg";
const char CSV_HEADLINE[] = "Descriptor,NumToilets,NumDoors,NumTempSensors";

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

const std::string ERR_MSG[] = {
	"ERR_BAD_QUERY",
	"ERR_BAD_ROOM_ID",
	"ERR_BAD_SENSOR_TYPE",
	"ERR_BAD_SENSOR_ID",
	"ERR_BAD_SENSOR_VAL"
};


class Server : public BasicServer {
public:	
	Server();
	~Server();
	void start(char port[]);
	
protected:
	void processRequest(char request[], char answer[]);
	
private:
	int build();
	int readCFG();
	int writeCFG();

	int process_get_request(std::string sensor_type, Room* requested_room, char response[]);
	int process_set_request(std::string sensor_type, Room* requested_room, std::string set_value, char response[]);
	int process_cfg_request(std::string cfg_query, Room* requested_room, char response[]);
	int process_cfg_update(char response[]);
	int process_cfg_add_room(char response[], Room* requested_room);
	int process_cfg_delete_room(char response[], Room* requested_room);

	void properties(char* out);
	Room* get_room_pointer(std::string roomDescr);
	int get_sensor_type(std::string sensor);

	int createRoom(std::string roomProps);
	int addRoom(std::string roomProps);
	int deleteRoom(std::string roomDescr);

	void print(std::string msg);
	void get_timestamp(std::string timestamp_string);

	std::vector<Room*> _rooms;
	std::vector<std::string> roomCFG;
};


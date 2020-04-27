#pragma once
#include "BasicServer.h"


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
	void start(char port[]);
	Server();
	~Server();
	

protected:
	virtual void processRequest(char request[], char answer[]);
	void properties();
};


#pragma once
#include "BasicServer.h"

class Server : public BasicServer {
public:
	void start(char port[]);
	Server();
	~Server();

protected:
	virtual void processRequest(char request[], char answer[]);
};


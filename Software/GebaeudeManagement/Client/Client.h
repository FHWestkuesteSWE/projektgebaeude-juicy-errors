#pragma once
#include "BasicClient.h"

class Client : public BasicClient
{
public:
	 //Client();
	Client(char server[], char port[]);
	// void sendRequest(const char request[], char answer[]);
	~Client();
protected:

}; 

#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <algorithm>
#include <cstdlib>
#include <iostream>

#include "Server.h"
#include "Building.h"


Server::Server() {
}

void Server::start(char port[]) {
	Building::Building();

	BasicServer::start(port);
}

void Server::processRequest(char req[], char ans[]) {
	std::cout << "processing request <";
	std::cout << req;
	std::cout << ">\n";
}

Server::~Server(){
}

#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <ctime>

#include "Server.h"
#include "Building.h"

using namespace std;



string getNthWord(string s, size_t n) {
	istringstream iss(s);
	while (n-- > 0 && (iss >> s));
	return s;
}

Server::Server() {
}

void Server::start(char port[]) {
	Building building;

	//for (int i = 0; i < NUM_ROOMS; i++) {
	//	cout << building._rooms[i]->getDescriptor << endl;
	//}

	BasicServer::start(port);
}

void Server::processRequest(char req[], char ans[]) {
	string request(req);
	string query, sensor, roomDescr, opt;
	int val, err = 0;

	query = getNthWord(request, 1);	
	sensor = getNthWord(request, 2);
	roomDescr = getNthWord(request, 3);

	opt = getNthWord(request, 4);
	cout << "opt <" << opt << ">" << endl;
	if (opt.compare(roomDescr)) opt = request.substr(request.find(opt));
	else opt.clear();

	// Debug
	cout << "query <" << query << ">" << endl;
	cout << "sensor <" << sensor << ">" << endl;
	cout << "roomDescr <" << roomDescr << ">" << endl;
	cout << "opt <" << opt << ">" << endl;

	cout << "processing request <" << req << ">" << endl;

	if (query.compare("get")) {
		switch (sensor) {
		case "Temp":
			// find index of ROOMDESCR in _rooms
			// set val to return of _rooms[index].getTemp()
			break;

		case "Door":
			break;

		case "Toilet":
			break;

		default:
			err = ERR_BAD_SENSOR_TYPE;
		}

	} else if (query.compare("set")) {
		switch (sensor) {
		case "Temp":
			// find index of ROOMDESCR in _rooms
			// check if opt only holds val
			// check if val is within range
			// IF VAL IN RANGE: call _rooms[index].setTemp(val)
			// IF VAL OUT OF RANGE: err = ERR_BAD_SENSOR_VAL
			break;

		case "Door":
			break;

		case "Toilet":
			break;

		default:
			err = ERR_BAD_SENSOR_TYPE;
		}

	} else {
		err = ERR_BAD_QUERY;
	}


	// SERVER RESPONSE
	// ...

}

Server::~Server(){
}
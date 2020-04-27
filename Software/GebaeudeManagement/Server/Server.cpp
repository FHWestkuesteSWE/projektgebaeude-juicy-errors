#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <ctime>

#include "Server.h"

using namespace std;


string getNthWord(string s, size_t n) {
	istringstream iss(s);
	while (n-- > 0 && (iss >> s));
	return s;
}

Server::Server() {
}

void Server::start(char port[]) {
	time_t mytime = time(nullptr);
	string timestamp(ctime(&mytime));
	timestamp = timestamp.substr(0, timestamp.length() - 1);

	cout << timestamp << " - Launching Server at 127.0.0.1 on Port " << port << endl;

	BasicServer::start(port);
}

void Server::processRequest(char req[], char ans[]) {
	string request(req);
	string query, sensorType, roomDescr, opt;
	int sensor, err = 0;
	char response[max_length];
	double val = 0.0;

	time_t mytime = time(nullptr);
	string timestamp(ctime(&mytime));
	timestamp = timestamp.substr(0, timestamp.length() - 1);

	query = getNthWord(request, 1);
	sensorType = getNthWord(request, 2);
	if (!sensorType.compare("Temp")) sensor = SENSOR_TEMP;
	else if (!sensorType.compare("Door")) sensor = SENSOR_DOOR;
	else if (!sensorType.compare("Toilet")) sensor = SENSOR_TOILET;
	else sensor = -1;

	roomDescr = getNthWord(request, 3);

	opt = getNthWord(request, 4);
	if (opt.compare(roomDescr)) opt = request.substr(request.find(opt));
	else opt.clear();

	// Debug
	//cout << "query <" << query << ">" << endl;
	//cout << "sensor <" << sensorType << ">" << endl;
	//cout << "roomDescr <" << roomDescr << ">" << endl;
	//cout << "opt <" << opt << ">" << endl;

	cout << timestamp << " - Q - " << req << endl;

	if (!query.compare("get")) {
		switch (sensor) {
		case SENSOR_TEMP:
			// TO DO 
			// find index of ROOMDESCR in _rooms
			// set val to return of _rooms[index].getTemp()
			val = 20.6;
			break;

		case SENSOR_DOOR:
			break;

		case SENSOR_TOILET:
			break;

		default:
			err = ERR_BAD_SENSOR_TYPE;
		}

	} else if (!query.compare("set")) {
		switch (sensor) {
		case SENSOR_TEMP:
			// TO DO 
			// find index of ROOMDESCR in _rooms
			// check if opt only holds val
			// check if val is within range
			// IF VAL IN RANGE: call _rooms[index].setTemp(val)
			// IF VAL OUT OF RANGE: err = ERR_BAD_SENSOR_VAL
			break;

		case SENSOR_DOOR:
			break;

		case SENSOR_TOILET:
			break;

		default:
			err = ERR_BAD_SENSOR_TYPE;
		}

	} else {
		err = ERR_BAD_QUERY;
	}


	sprintf(response, "%s %s %s %.2lf", query.c_str(), sensorType.c_str(), roomDescr.c_str(), val);
	
	if (err != 0) {
		sprintf(response, "Error %i\n", err);
	}

	strncpy(ans, response, std::min<int>(max_length, strlen(ans) + 1));
	cout << timestamp << " - A - " << response << endl;
}

Server::~Server(){
}
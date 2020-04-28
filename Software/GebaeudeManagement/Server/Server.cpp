#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>

#include "Server.h"

using namespace std;


Server::Server() {
}

// TAKEN FROM http://www.cplusplus.com/forum/beginner/99171/
string getNthWord(string s, size_t n) {
	istringstream iss(s);
	while (n-- > 0 && (iss >> s));
	return s;
}

// appends string vector DATA by the contents of istream IN
void loadCSV(istream &in, vector<string> &data) {
	string tmp;

	while (!in.eof()) {
		getline(in, tmp, '\n');                     // get next line
		data.push_back(tmp);						// append vector

		// DEBUG OUTPUT
		//cout << tmp << '\n';

		tmp.clear();
	}
}

void Server::start(char port[]) {
	if (build() != EXIT_SUCCESS) {
		this->print(" - Could not initialize building ");
		this->print(" - Terminating service ");
		return;
	}

	this->print("Building initialized");
	this->print("Launching Server at 127.0.0.1 on Port ");

	BasicServer::start(port);
}

void Server::print(std::string msg) {
	time_t mytime = time(nullptr);
	string timestamp(ctime(&mytime));
	timestamp = timestamp.substr(0, timestamp.length() - 1);

	cout << timestamp << " - SYS - " << msg << endl;
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

	// DEBUG OUTPUT
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

		sprintf(response, "%s %s %s %.2lf", query.c_str(), sensorType.c_str(), roomDescr.c_str(), val);

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

		sprintf(response, "%s %s %s %.2lf", query.c_str(), sensorType.c_str(), roomDescr.c_str(), val);

	} else if (!query.compare("cfg")) {
		if (!sensorType.compare("-g")) {
			this->properties(response);
		} else if (!sensorType.compare("-u")) {
			this->updateCFG();
			this->properties(response);
		}
	} else {
		err = ERR_BAD_QUERY;
	}
	
	// error handling
	if (err != 0) {
		sprintf(response, "Error %i\n", err);
	}

	// copy response to server answer
	strncpy(ans, response, min<int>(max_length, strlen(ans) + 1));
	cout << timestamp << " - A - " << response << endl;
}

void Server::properties(char* out) {
	string temp1, temp2;

	for (auto i = roomCFG.cbegin(); i != roomCFG.cend(); i++) {
		temp1 = *i;
		temp1 = getNthWord(temp1, 1);
		temp2.append(temp1);	
	}
	strncpy(out, temp2.c_str(), min<int>(max_length, strlen(out) + 1));
	temp1.erase();
	temp2.erase();
}

int Server::getCFG() {
	// FOR FILE HANDLING REFER TO http://www.cplusplus.com/doc/tutorial/files/
	// Check if a config file exists
	if (!ifstream(CONFIG_NAME)) {

		// try to create new file
		std::ofstream cfg(CONFIG_NAME);
		if (!cfg) {
			this->print("Could not create config file");
		}
		else {
			this->print("Created new config file");
		}

		return EXIT_FAILURE;
	}

	// read existing config file
	std::ifstream cfg(CONFIG_NAME);
	if (!cfg) {
		this->print("Could not open existing config file");
		return EXIT_FAILURE;
	}

	roomCFG.clear();
	loadCSV(cfg, roomCFG);

	// DEBUG OUTPUT
	//for (auto i = rooms.cbegin(); i != rooms.cend(); i++) {
	//	cout << *i << '\n';
	//}

	return EXIT_SUCCESS;
}

void Server::updateCFG() {
	if (this->getCFG() != EXIT_SUCCESS) {
		this->print("Could not update server config");
	} else {
		this->print("Server config successfully updated");
	}
}

int Server::build() {
	if (this->getCFG() != EXIT_SUCCESS) {
		this->print("Could not load server config");
		return EXIT_FAILURE;
	}
	

	// build rooms here
	// ...


	return EXIT_SUCCESS;
}

int Server::addRoom(std::string descr, int numToilets, int numDoors, int numTempSensors) {


	return EXIT_SUCCESS;
}

int Server::deleteRoom(std::string descr) {


	return EXIT_SUCCESS;
}

Server::~Server(){
}
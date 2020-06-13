#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#include "Server.h"
#include "FileHandling.h"

using namespace std;

// TEST: no
//
Server::Server() {
}

// TAKEN FROM http://www.cplusplus.com/forum/beginner/99171/
// get the n-th word of a given string s
// TEST: no
//
string getNthWord(string s, size_t n) {
	istringstream iss(s);
	while (n-- > 0 && (iss >> s));
	return s;
}


// TEST: no port given, no \0 in char[]
//
// start the server
void Server::start(char port[]) {
	std::string str = string("Launching Server at 127.0.0.1 on Port ");
	str.append(port);
	
	if (build() != EXIT_SUCCESS) {
		this->print("Failed to initialize building");
		this->print("Terminating service");
		return;
	}
	this->print("Building initialized");
	this->print(str);

	BasicServer::start(port);
}


// TEST: no
//
// print system message on server console
void Server::print(const std::string msg) {
	std::string timestamp;
	this->get_timestamp(&timestamp);

	cout << timestamp << " - SYS - " << msg << endl;
}

// TEST: no \0 in char[], char[] empty, all possible correct requests types give right answer, 
//		false requests are detected
//
// process incoming Server Request
void Server::processRequest(char req[], char ans[]) {
	std::string request(req);
	std::string query, sensor, room_descriptor, optional;
	Room* requested_room = NULL;
	std::string timestamp;	
	char response[max_length];


	// build timestamp string	
	this->get_timestamp(&timestamp);

	// retrieve information from the request string
	//this->divide_request_into_substrings(request, query, sensor, room_descriptor, optional);
	this->divide_request_into_substrings(&request, &query, &sensor, &room_descriptor, &optional);

	// DEBUG OUTPUT
	//cout << "request <" << request << ">" << endl;
	//cout << "query <" << query << ">" << endl;
	//cout << "sensor <" << sensor << ">" << endl;
	//cout << "room_descriptor <" << room_descriptor << ">" << endl;
	//cout << "optional <" << optional << ">" << endl;

	// print request on server terminal
	cout << timestamp << " - Req - " << req << endl;


	// choose desired action based on query
	requested_room = this->get_room_pointer(room_descriptor);
	if (requested_room == NULL && query.compare("cfg")) {
		this->print("Room does not exist");
		sprintf(response, "%s %s %s %s", query.c_str(), sensor.c_str(), room_descriptor.c_str(), ERR_MSG[ERR_BAD_ROOM_ID].c_str());
	}
	else if (!query.compare("get")) {
		this->process_get_request(sensor, requested_room, response);
	}
	else if (!query.compare("set")) {
		this->process_set_request(sensor, requested_room, optional, response);
	}
	else if (!query.compare("cfg")) {
		this->process_cfg_request(sensor, requested_room, response);
	}
	else {
		sprintf(response, "%s %s %s %s", query.c_str(), sensor.c_str(), room_descriptor.c_str(), ERR_MSG[ERR_BAD_QUERY].c_str());
	}

	// copy response to server answer
	strncpy(ans, response, std::min(max_length, (const int)strlen(ans) + 1));

	// print response on server terminal
	cout << timestamp << " - Ans - " << response << endl;
}


//oid Server::divide_request_into_substrings(std::string request, std::string query, std::string sensor, std::string room_descriptor, std::string optional) {
void Server::divide_request_into_substrings(std::string *request, std::string *query, std::string *sensor, std::string *room_descriptor, std::string *optional) {
	// copy the words from the request string into the substrings accordingly
	query->assign(getNthWord(*request, 1));
	sensor->assign(getNthWord(*request, 2));
	room_descriptor->assign(getNthWord(*request, 3));
	optional->assign(getNthWord(*request, 4));

	// check if the request had an optional argument,
	// if yes, copy the remaining characters of the request into the optional string,
	// if not clear the optional string	
	if (optional->compare(*room_descriptor) == 0) optional->clear();
	else optional->assign(request->substr(request->find(*optional)));

	// check if the request string had a room_descriptor, 
	// if not clear the room_descriptor string	
	if (room_descriptor->compare(*sensor) == 0) room_descriptor->clear();
}


void Server::get_timestamp(std::string *in) {
	time_t mytime = time(nullptr);
	std::string timestamp_string(ctime(&mytime));
	timestamp_string = timestamp_string.substr(0, timestamp_string.length() - 1);
	
	in->assign(timestamp_string);
}


// returns a pointer to the room with the descriptor descr in vector _rooms
// returns NULL if the room does not exist
Room* Server::get_room_pointer(std::string roomDescr) {
	for (int i = 0; i < _rooms.size(); i++) {
		if (_rooms[i]->getDescriptor().compare(roomDescr) == 0) {
			_rooms[i]->getDescriptor();
			return _rooms[i];
		}
	}

	return NULL;
}


int Server::get_sensor_type(std::string sensor) {
	if (!sensor.compare("temp")) return SENSOR_TEMP;
	else if (!sensor.compare("door")) return SENSOR_DOOR;
	else if (!sensor.compare("toilet")) return SENSOR_TOILET;
	else if (!sensor.compare("window")) return SENSOR_WINDOW;
	else return -1;
}


int Server::process_get_request(std::string sensor_type, Room *requested_room, char response[]) {
	double get_value = 0.0;

	switch (this->get_sensor_type(sensor_type)) {
	case SENSOR_TEMP:
		get_value = requested_room->getTemperature();
		sprintf(response, "%s %s %s %.2lf", "get", sensor_type.c_str(), requested_room->getDescriptor().c_str(), get_value);
		break;

	case SENSOR_DOOR:
		get_value = (float)requested_room->getDoorStatus(0);
		sprintf(response, "%s %s %s %i", "get", sensor_type.c_str(), requested_room->getDescriptor().c_str(), (int)get_value);
		break;

	case SENSOR_TOILET:
		get_value = (float)requested_room->getToiletStatus(0);
		sprintf(response, "%s %s %s %i", "get", sensor_type.c_str(), requested_room->getDescriptor().c_str(), (int)get_value);
		break;

	case SENSOR_WINDOW:
		get_value = (float)requested_room->getWindowStatus();
		sprintf(response, "%s %s %s %i", "get", sensor_type.c_str(), requested_room->getDescriptor().c_str(), (int)get_value);

	default:
		sprintf(response, "%s %s %s %s", "get", sensor_type.c_str(), requested_room->getDescriptor().c_str(), ERR_MSG[ERR_BAD_SENSOR_TYPE].c_str());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}


int Server::process_set_request(std::string sensor_type, Room* requested_room, std::string set_value, char response[]) {
	switch (this->get_sensor_type(sensor_type)) {
	case SENSOR_TEMP:
		requested_room->setTemperature(atoi(set_value.c_str()));
		break;

	case SENSOR_DOOR:
		requested_room->openCloseDoor(0, atoi(set_value.c_str()));
		break;

	default:
		sprintf(response, "%s %s %s %s", "set", sensor_type.c_str(), requested_room->getDescriptor().c_str(), ERR_MSG[ERR_BAD_SENSOR_TYPE].c_str());
		return EXIT_FAILURE;
	}

	sprintf(response, "%s %s %s %s", "set", sensor_type.c_str(), requested_room->getDescriptor().c_str(), set_value.c_str());
	return EXIT_SUCCESS;
}


int Server::process_cfg_request(std::string cfg_query, Room* requested_room, char response[]) {
	if (!cfg_query.compare("-g")) {
		this->properties(response);
	}
	else if (!cfg_query.compare("-u")) {
		this->process_cfg_update(response);
	}
	else if (!cfg_query.compare("-a")) {
		this->process_cfg_add_room(response, requested_room);
	}
	else if (!cfg_query.compare("-d")) {
		this->process_cfg_delete_room(response, requested_room);
	}
	else {
		sprintf(response, "%s %s %s %s", "cfg", cfg_query.c_str(), requested_room->getDescriptor().c_str(), ERR_MSG[ERR_BAD_QUERY].c_str());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}


int Server::process_cfg_update(char response[]) {
	if (this->readCFG() != EXIT_SUCCESS) {
		this->print("Could not update server config");
		sprintf(response, "%s %s %s", "cfg", "-g", "ERR_BAD_CFG");
		return EXIT_FAILURE;
	}
	else {
		this->print("Server config successfully updated");
		this->properties(response);
	}

	return EXIT_SUCCESS;
}


int Server::process_cfg_add_room(char response[], Room* requested_room) {
	if (this->addRoom(requested_room->getDescriptor()) != EXIT_SUCCESS) {
		this->print("Could not add room");
		sprintf(response, "%s %s %s %s", "cfg", "-a", requested_room->getDescriptor().c_str(), "ERR_BAD_ROOM");
		return EXIT_FAILURE;
	}
	else {
		this->print("New room successfully added");
		this->properties(response);
	}

	return EXIT_SUCCESS;
}


int Server::process_cfg_delete_room(char response[], Room* requested_room) {
	if (this->deleteRoom(requested_room->getDescriptor()) != EXIT_SUCCESS) {
		this->print("Could not delete room");
		sprintf(response, "%s %s %s %s", "cfg", "-d", requested_room->getDescriptor().c_str(), "ERR_BAD_ROOM");
		return EXIT_FAILURE;
	}
	else {
		this->print("Room successfully deleted");
		this->properties(response);
	}

	return EXIT_SUCCESS;
}


//TEST: rooms does not exist, correct answer is returned
//
// save the room configuration of the server to char array OUT
void Server::properties(char* out) {
	string temp1, temp2;

	for (std::vector<std::string>::const_iterator i = roomCFG.cbegin(); i != roomCFG.cend(); i++) { //Entwurfsmuster: Iterator-Pattern
		temp1 = *i;
		temp1 = getNthWord(temp1, 1);
		temp1.append(" ");
		temp2.append(temp1);	
	}
	strncpy(out, temp2.c_str(), std::min(max_length, (const int)strlen(out) + 1));
	temp1.erase();
	temp2.erase();
}


// TEST: (fileNotFound in loadCSV), headline has been removed, vector is filled
//
// read the room configuration from the config file, saves config to global vector roomCFG
int Server::readCFG() {
	char const* filename = CONFIG_NAME;

	roomCFG.clear();
	if (!txt_read(filename, roomCFG)) {
		this->print("Could not access config file");
		return EXIT_FAILURE;
	}

	// remove CSV headline
	roomCFG.erase(roomCFG.cbegin());

	return EXIT_SUCCESS;
}

// TEST: (fileNotFound in writeCSV), output file structure is correct
//
// write the room configuration to the config file
int Server::writeCFG() {
	char const* filename = CONFIG_NAME;

	// add CSV Headline at the beginning
	std::reverse(roomCFG.begin(), roomCFG.end());
	roomCFG.push_back(CSV_HEADLINE);
	std::reverse(roomCFG.begin(), roomCFG.end());

	if (txt_truncate(filename, roomCFG)) {
		roomCFG.erase(roomCFG.cbegin());		// remove CSV headline

		return EXIT_SUCCESS;
	}
	else  {
		roomCFG.erase(roomCFG.cbegin());		// remove CSV headline

		return EXIT_FAILURE;
	}
}

// TEST: no
//
// build the server architecture based on the preloaded room configuration
int Server::build() {
	// read config from file
	if (this->readCFG() != EXIT_SUCCESS) {
		this->print("Failed to load server config");
		return EXIT_FAILURE;
	}
	
	// create rooms according to config
	for (std::vector<std::string>::const_iterator i = roomCFG.cbegin(); i != roomCFG.cend(); i++) {  //Entwurfsmuster: Iterator-Pattern
		createRoom(*i);
	}

	return EXIT_SUCCESS;
}


// TEST: formatting of roomProps correct and false, or roomProps NULL or empty
//
// add a room to the server configuration
int Server::createRoom(const std::string roomProps) {
	std::string descr;
	int numToilets, numDoors, numTempSensors;
	Room* rp;

	descr = getNthWord(roomProps, 1);
	numToilets = std::stoi(getNthWord(roomProps, 2));
	numDoors = std::stoi(getNthWord(roomProps, 3));
	numTempSensors = std::stoi(getNthWord(roomProps, 4));

	//Room r = Room(descr, numToilets, numDoors, numTempSensors);
	rp = new Room(descr, numToilets, numDoors, numTempSensors, false); //no windows as default
	_rooms.push_back(rp);

	return EXIT_SUCCESS;
}


// TEST: no
//
// add a room to the server configuration and update 
int Server::addRoom(std::string roomProps) {
	//_rooms.push_back(createRoom(roomProps));
	roomCFG.push_back(roomProps);
	writeCFG();

	return EXIT_SUCCESS;
}


// TEST: roomDescr NULL or empty, error thrown if no room exists
//
// delete a room from the server configuration
int Server::deleteRoom(std::string roomDescr) {
	Room *room_to_remove = this->get_room_pointer(roomDescr);
	
	if (room_to_remove == NULL) {
		this->print("Room does not exist!");
			return EXIT_FAILURE;
	}

	this->print("NEED FUNCTION TO REMOVE ROOM HERE!");
	// delete found room
	//room_to_remove->
	//_rooms.erase(room_to_remove);
	//if (writeCFG())	return EXIT_SUCCESS;
	return EXIT_SUCCESS;
}

// TEST: no
//
Server::~Server(){
}
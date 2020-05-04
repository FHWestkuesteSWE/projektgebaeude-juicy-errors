#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#include "Server.h"

using namespace std;


Server::Server() {
}

// TAKEN FROM http://www.cplusplus.com/forum/beginner/99171/
// get the n-th word of a given string s
string getNthWord(string s, size_t n) {
	istringstream iss(s);
	while (n-- > 0 && (iss >> s));
	return s;
}

// append string vector DATA by the contents of istream IN
void loadCSV(istream &in, vector<string> &data) {
	string temp;

	while (!in.eof()) {
		getline(in, temp, '\n');                    // get next line
		data.push_back(temp);						// append vector

		// DEBUG OUTPUT
		//cout << tmp << '\n';

		temp.clear();
	}
}

// append string to file
void writeCSV(ostream& out, string data) {
	data = "\n" + data;
	out.write(data.c_str(), data.size());
}

// start the server
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

// print system message on server console
void Server::print(std::string msg) {
	time_t mytime = time(nullptr);
	string timestamp(ctime(&mytime));
	timestamp = timestamp.substr(0, timestamp.length() - 1);

	cout << timestamp << " - SYS - " << msg << endl;
}

// process incoming Server Request
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
	if (opt.compare(roomDescr) == 0) opt.clear();
	else opt = request.substr(request.find(opt));		// if there are optional arguments available write them to optopt.clear();

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
			if (this->readCFG() != EXIT_SUCCESS) {
				this->print("Could not update server config");
			} else {
				this->print("Server config successfully updated");
				this->properties(response);
			}			
		} else if (!sensorType.compare("-a")) {
			if (this->addRoom(roomDescr.append(opt)) != EXIT_SUCCESS) {
				this->print("Could not add room");
			} else {
				this->print("New room successfully added");
				this->properties(response);
			}
		} else if (!sensorType.compare("-d")) {
			if (this->deleteRoom(roomDescr) != EXIT_SUCCESS) {
				this->print("Could not delete room");
			} else {
				this->print("Room successfully deleted");
				this->properties(response);
			}
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

// save the room configuration of the server to char array OUT
void Server::properties(char* out) {
	string temp1, temp2;

	for (auto i = roomCFG.cbegin(); i != roomCFG.cend(); i++) {
		temp1 = *i;
		temp1 = getNthWord(temp1, 1);
		temp1.append(" ");
		temp2.append(temp1);	
	}
	strncpy(out, temp2.c_str(), min<int>(max_length, strlen(out) + 1));
	temp1.erase();
	temp2.erase();
}

// read the room configuration from the config file, saves config to global vector roomCFG
int Server::readCFG() {
	// FOR FILE HANDLING REFER TO http://www.cplusplus.com/doc/tutorial/files/
	char const* filename = CONFIG_NAME;
	ifstream cfg(filename);		// opens file if file exists, does not create new file if file doesn't exist
	
	// Check if a config file exists
	if (!cfg.good()) {
		this->print("Config file does not exist");
		return EXIT_FAILURE;
	}

	// read existing config file
	if (!cfg.is_open()) {
		this->print("Could not open existing config file");
		return EXIT_FAILURE;
	}

	roomCFG.clear();
	loadCSV(cfg, roomCFG);
	cfg.close();

	// remove CSV headline
	roomCFG.erase(roomCFG.cbegin());

	return EXIT_SUCCESS;
}

// write the room configuration to the config file
int Server::writeCFG() {
	// FOR FILE HANDLING REFER TO http://www.cplusplus.com/doc/tutorial/files/
	char const *filename = TESTING_NAME;
	fstream cfg(filename);								// opens file if file exists, does not create new file if file doesn't exist

	// Check if a config file exists
	if (!cfg.good()) {
		this->print("Config file does not exist");

		// if file does not exist, create new file
		cfg.open(filename, ios::out | ios::trunc);		// this is what creates the new file
		if (cfg.is_open()) {
			this->print("Created new config file");					
		} else {
			this->print("Could not create config file");
			return EXIT_FAILURE;
		}
	} 
	cfg.close();

	// write to existing config file
	cfg.open(filename, ios::out | ios::trunc);		
	if (cfg.is_open()) {
		cfg.clear();
		//cfg.seekp(0, ios::beg);						// seek is not needed since ios::trunc deletes previous content and sets seekp to 0
		cfg << CSV_HEADLINE;
		for (auto i = roomCFG.cbegin(); i != roomCFG.cend(); i++) {
			cfg << *i << '\n';
		}
		cfg.close();
	} else {
		this->print("Could not write on existing config file");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

// build the server architecture based on the preloaded room configuration
int Server::build() {
	// read config from file
	if (this->readCFG() != EXIT_SUCCESS) {
		this->print("Could not load server config");
		return EXIT_FAILURE;
	}
	
	// create rooms according to config
	for (int i = 0; i < roomCFG.size(); i++) {
		createRoom(roomCFG[i]);
	}

	for (int i = 0; i < _rooms.size(); i++)
	{
		cout << "\n\ngetNumDoors: " << (*(_rooms[i])).getNumDoors() << "\n";
	}

	return EXIT_SUCCESS;
}

// add a room to the server configuration
int Server::createRoom(std::string roomProps) {
	std::string descr;
	int numToilets, numDoors, numTempSensors;
	Room* rp;

	descr = getNthWord(roomProps, 1);
	numToilets = std::stoi(getNthWord(roomProps, 2));
	numDoors = std::stoi(getNthWord(roomProps, 3));
	numTempSensors = std::stoi(getNthWord(roomProps, 4));

	Room r = Room(descr, numToilets, numDoors, numTempSensors);
	rp = &r;
	_rooms.push_back(rp);

	return EXIT_SUCCESS;
}

// add a room to the server configuration and update 
int Server::addRoom(std::string roomProps) {
	//_rooms.push_back(createRoom(roomProps));
	roomCFG.push_back(roomProps);
	writeCFG();

	return EXIT_SUCCESS;
}

// delete a room from the server configuration
int Server::deleteRoom(std::string roomDescr) {
	int i = 0;

	// find room with the given roomDescr
	while (roomCFG[i].compare(roomDescr) != 0) {
		i++;
		if (i == roomCFG.size()) {
			return EXIT_FAILURE;
		}
	}
	
	// delete found room
	_rooms.erase(_rooms.cbegin() + i);
	writeCFG();

	return EXIT_SUCCESS;
}

Server::~Server(){
}
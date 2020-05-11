#include "FileHandling.h"


// append string vector DATA by the contents of istream IN
bool txt_read(const char *filename, vector<string> &data) {
	string temp;
	std::ifstream file;
	file.open(filename, std::ifstream::in);

	// return EXIT_FAILURE if config file does not exist or cant be accessed
	if (!file.good()) {
		return false;
	}

	while (!file.eof()) {
		getline(file, temp, '\n');					// get next line
		data.push_back(temp);						// append vector

		// DEBUG OUTPUT
		//cout << temp << '\n';

		temp.clear();
	}
	file.close();

	return true;
}


// Truncate file with content of DATA, overwriting all previous data in the process
bool txt_truncate(const char* filename, vector<string>& data) {
	fstream file(filename);								// opens file if file exists, does not create new file if file doesn't exist

	// Check if a config file exists
	if (!txt_exists(filename)) {

		// if file does not exist, create new file
		file.open(filename, ios::out | ios::trunc);		// this is what creates the new file

		// return EXIT_FAILURE if config file could not be created
		if (!file.is_open()) {
			file.clear();
			return false;
		}
	}
	file.close();

	// write to existing config file
	file.open(filename, ios::out | ios::trunc);
	if (file.is_open()) {
		for (auto i = data.cbegin(); i != data.cend(); i++) {
			file << *i << '\n';
		}
		file.close();
	} else {
		file.clear();
		return false;
	}
	
	return true;
}



// append string to file
bool txt_putLine(const char* filename, string &line) {
	fstream file(filename);								// opens file if file exists, does not create new file if file doesn't exist

	// Check if a config file exists
	if (!txt_exists(filename)) {
		file.clear();
		return false;
	}
	file.close();
	
	// write to existing config file
	file.open(filename, ios::out | ios::app);
	if (file.is_open()) {
		file << line << '\n';
		file.close();
	}
	else {
		file.clear();
		return false;
	}
	
	return true;
}


// check if a file exists, returns TRUE if exists and FALSE if does not exist
bool txt_exists(const char* filename) {
	ifstream file(filename);

	return file.good();
}
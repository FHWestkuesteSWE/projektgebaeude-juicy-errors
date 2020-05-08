#include "FileHandling.h"


// append string vector DATA by the contents of istream IN
int loadCSV(const char *filename, vector<string>& data) {
	string temp;
	std::ifstream in;
	in.open(filename, std::ifstream::in);

	// return EXIT_FAILURE if config file does not exist or cant be accessed
	if (!in.good()) {
		return EXIT_FAILURE;
	}

	while (!in.eof()) {
		getline(in, temp, '\n');                    // get next line
		data.push_back(temp);						// append vector

		// DEBUG OUTPUT
		//cout << temp << '\n';

		temp.clear();
	}
	in.close();

	return EXIT_SUCCESS;
}



// append string to file
int writeCSV(ostream& out, string data) {

	data = "\n" + data;
	out.write(data.c_str(), data.size());

	return EXIT_SUCCESS;
}
#include "Server.h"

int main(int argc, char* argv[]) {
	Server server; 

	server.start(argv[1]);

	return 0;
}
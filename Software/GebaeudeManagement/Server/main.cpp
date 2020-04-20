#include "Server.h"
#include "Building.h"

int main(int argc, char* argv[]) {
	Server s; 
	Building b;
	s.start(argv[1]);
	return 0;
}
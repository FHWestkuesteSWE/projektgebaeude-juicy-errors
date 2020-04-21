#include "BasicServer.h"
#include "Building.h"

int main(int argc, char* argv[]) {
	BasicServer s; 
	Building b;

	s.start(argv[1]);

	return 0;
}
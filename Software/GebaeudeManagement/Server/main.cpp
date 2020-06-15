#include "Server.h"
#include "TemperatureSensor.h"
#include "Room.h"


//int main(int argc, char* argv[]) {
//	Room *r;	
//	r = new Room("testRoom", 0, 0, 3, false);
//
//	for (int i = 0; i < 5; i++) {
//		std::cout << r->getTemperature() << std::endl;
//	}
//
//	//std::cout << r->getTemperature() << std::endl;
//	//std::cout << r->getNumTempSensors() << std::endl;
//
//
//	//std::vector<TemperatureSensor*> _temperatureSensors;
//	//TemperatureSensor t;
//	//for (int i = 0; i < 5; i++) {
//	//	_temperatureSensors.push_back(&TemperatureSensor());
//	//}
//
//	//std::cout << "normal assignment " << t.getTemp() << std::endl;
//	////std::cout << "normal assignment " << &t << std::endl;
//
//	//for (int i = 0; i < 5; i++) {
//	//	std::cout << "array " << _temperatureSensors[i]->getTemp() << std::endl;
//	//	//std::cout << "array " << &_temperatureSensors[i] << std::endl;
//	//}
//
//	return 0;
//}


int main(int argc, char* argv[]) {
	Server s;

	s.start((argv[1]));

	return 0;
}
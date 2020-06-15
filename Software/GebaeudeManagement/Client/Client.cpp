#include "Client.h"

Client::Client (char _server[], char _port[]): BasicClient(_server, _port) 
{
  
}

Client::~Client() 
{

}
  
char * Client::getStrReq ( void )
{
  return &request[0]; 
}
  
char * Client::getStrAns ( void )
{
  return &answer[0]; 
}

void Client::client_send_request () 
{
    int res = 0;
    do {
        res = sendRequest(request, answer);
        if (res == ERR_ABORT) {
            std::cout << "Could not reach server. Aborting program..." << std::endl;
            exit(-1);
        }
    } while (res == ERR_RETRY);
}


int Client::select_sensor_or_actuator ( int room_number ) 
{
    char choice;

    do {
        print_select_sensor_menu();
        getKBEntry(&choice);
        /* cout << "Choice: " << choice << endl; */
        std::cout << "\n\n";

        switch (choice) {
        case 't':
            return select_query_for_chosen_sensor (room_number, SENSOR_TEMP);

        case 'd':
            return select_query_for_chosen_sensor (room_number, SENSOR_DOOR);
            //return SENSOR_DOOR;

        case 'l':
            return select_query_for_chosen_sensor (room_number, SENSOR_TOILET);
            //return SENSOR_TOILET;

        case 'w':
            return select_query_for_chosen_sensor (room_number, SENSOR_WINDOW);
            //return SENSOR_WINDOW;

        default:
            break;
        }        
    } while (1);
}


int Client::select_query_for_chosen_sensor (int room_number, SENSOR_TYPES sensor_type) 
{
    switch (sensor_type) {
    case SENSOR_TEMP:
        return execute_query_temp(room_number);

    case SENSOR_DOOR:
        return execute_query_door(room_number);

    case SENSOR_TOILET:
        return execute_query_toilet(room_number);

    case SENSOR_WINDOW:
        return execute_query_window(room_number);

    default:
        return EXIT_FAILURE;
    }
}


int Client::execute_query_temp (int room_number) 
{
    char choice;
    int set_value = 0;

    do {
      std::cout << "(g)et temperature reading" << std::endl;
      std::cout << "(s)et desired temperature" << std::endl;
      std::cout << "----------------------------------------------------" << std::endl; 
      std::cout << "Choice: "; 

        getKBEntry(&choice);
        std::cout << "\n\n";

        switch (choice) {
        case 'g':
            sprintf(request, "get temp %s", roomDescriptors[room_number].c_str());
            this->client_send_request();
            return EXIT_SUCCESS;

        case 's':
            std::cout << "Set Value: ";
            set_value = getKBEntry(NULL);

            sprintf(request, "set temp %s %.2lf", roomDescriptors[room_number].c_str(), (float)set_value);
            this->client_send_request();
            return EXIT_SUCCESS;

        default:
            break;
        }
    } while (1);
}


int Client::execute_query_door (int room_number) 
{
    char choice;
    int set_value = 0;

    do {
      std::cout << "(g)et door status" << std::endl;
      std::cout << "(l)ock the door" << std::endl;
      std::cout << "(u)nlock the door" << std::endl;
      std::cout << "----------------------------------------------------" << std::endl; 
      std::cout << "Choice: "; 

        getKBEntry(&choice);
        std::cout << "\n\n";

        switch (choice) {
        case 'g':
            sprintf(request, "get door %s", roomDescriptors[room_number].c_str());
            client_send_request();
            return EXIT_SUCCESS;

        case 'l':
            sprintf(request, "set door %s %i", roomDescriptors[room_number].c_str(), 1);
            client_send_request();
            return EXIT_SUCCESS;

        case 'u':
            sprintf(request, "set door %s %i", roomDescriptors[room_number].c_str(), 0);
            client_send_request();
            return EXIT_SUCCESS;

        default:
            break;
        }
    } while (1);
}


int Client::execute_query_toilet (int room_number) 
{
    char choice;
    int set_value = 0;

    do {
      std::cout << "(g)et toilet sensor status" << std::endl;
      std::cout << "----------------------------------------------------" << std::endl; 
      std::cout << "Choice: "; 

        getKBEntry(&choice);
        std::cout << "\n\n";

        switch (choice) {
        case 'g':
            sprintf(request, "get toilet %s", roomDescriptors[room_number].c_str());
            client_send_request();
            return EXIT_SUCCESS;

        default:
            break;
        }
    } while (1);
}


int Client::execute_query_window (int room_number) 
{
    char choice;
    int set_value = 0;

    do {
      std::cout << "(g)et window status" << std::endl;
      std::cout << "(o)pen the windows" << std::endl;
      std::cout << "(c)lose the windows" << std::endl;
      std::cout << "----------------------------------------------------" << std::endl; 
      std::cout << "Choice: "; 

        getKBEntry(&choice);
        std::cout << "\n\n";

        switch (choice) {
        case 'g':
            sprintf(request, "get window %s", roomDescriptors[room_number].c_str());
            client_send_request();
            return EXIT_SUCCESS;

        case 'o':
            sprintf(request, "set window %s %i", roomDescriptors[room_number].c_str(), 0);
            client_send_request();
            return EXIT_SUCCESS;

        case 'c':
            sprintf(request, "set window %s %i", roomDescriptors[room_number].c_str(), 1);
            client_send_request();
            return EXIT_SUCCESS;

        default:
            break;
        }
    } while (1);
}


// TEST: check return value against input value, check out of range behaviour
// for selection
int Client::selectRoom ( void )
{ 
  // get initial building configuration from server
  strcpy(request, "cfg -g");
  client_send_request();
        
  // retrieve room descriptors from the answer and save them in the vector roomDescriptors
  splitString ( (std::string)answer, roomDescriptors, ' ' );

  int 
    choice, 
    roomCount = (int)roomDescriptors.size();
  //cout << "Number of rooms: " << roomDescriptors.size() << endl;
        
  std::cout << "----------------------------------------------------" << std::endl;
  std::cout << "Please select a room \n";
  std::cout << "----------------------------------------------------" << std::endl; 
  for ( int i = 0; i < roomCount; i++ ) {
    std::cout << "(" << i << ")\t" << roomDescriptors[i] << "\n";
  }
  //cout << "\n\n(q)uit program" << endl;
  std::cout << "----------------------------------------------------" << std::endl; 
  std::cout << "Choice: (0 - " << roomCount-1 << "): ";
  choice = getKBEntry (NULL); 
  std::cout << "\n\n";

  if ( ( choice >= 0 ) && ( choice < roomCount ) ) return choice;
  else return -1; // wrong entry
}


void Client::print_select_sensor_menu() 
{
  std::cout << "----------------------------------------------------" << std::endl;
  std::cout << "Please select the desired sensor or actuator" << "\n";
  std::cout << "----------------------------------------------------" << std::endl; 
  std::cout << "(t)emperature management" << std::endl;
  std::cout << "(d)oor access control" << std::endl;
  std::cout << "(l)avatory management" << std::endl;
  std::cout << "(w)indow control" << std::endl;
    //cout << "\n\n(b)ack" << endl;
  std::cout << "----------------------------------------------------" << std::endl; 
  std::cout << "Choice: ";
}


// returns user input (changes behavior for UNITTEST)
int Client::getKBEntry ( char * kbentry )
{
#ifdef UNITTEST
  if ( !kbentry ) {
    return kbRetVal;
  }
  else {
    kbentry[0] = kbRetValCh; // return default
    return 0;
  } 
#else
  if ( !kbentry ) {
    int choice; // = 0;
    std::string s_choice;
    std::cin >> s_choice; 
    try { choice = stoi (s_choice); }
    catch (std::invalid_argument e) { choice = -1; }
    // clear cin buffer
    std::cin.ignore(INT_MAX, '\n');
    std::cin.clear(); 
    return choice;
  }
  else {
    std::cin >> kbentry[0];
    // clear cin buffer
    std::cin.ignore(INT_MAX, '\n');
    std::cin.clear(); 
    return 0;
  }
#endif 
  return -1;
}


// third party code (stackoverflow.com)
int Client::splitString ( const std::string &txt, std::vector<std::string> &strs, char ch )
{
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    /* strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) ); */
    /*   cout << "Pushing string to list: " << txt.substr ( initialPos, std::min (pos, txt.size() ) - initialPos + 1 ) << endl; */

    return (int)strs.size();
}


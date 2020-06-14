// main.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms :).

//#define UNITTEST

#include "main.h"

/* #include "../Server/FileHandling.h" */

#ifdef UNITTEST
  int kbRetVal = 42; // default integer return value for keyboard entry
  char kbRetValCh = 'f'; // default char return value for keyboard entry
#endif

std::vector<std::string> roomDescriptors; // list of room descriptors from server
using namespace std;



//int main(int argc, char* argv[]) 
//{
//    Client c(argv[1], argv[2]);
//    char req[1024];
//    char ans[1024];
//    // int numRooms = 0; // number of configured rooms
//
//    int roomNumber = -1;
//    int roomAction = 0; // either GET_VALUE or SET_VALUE
//    int value = 0; // set value 
//    
//    std::cout << "\n\n-=[ BuildingMaster FHW 3000 ]=-\n\n";
//    std::cout << "(Ctrl-c to quit)\n\n" << endl;
//
//    int res = 0;
//
//    do {
//    // -----------------------------------------------------------------------
//    // MENU: select room (root)
//    // -----------------------------------------------------------------------
//
//    // get initial building configuration from server
//    strcpy(req, "cfg -g");
//    client_send_request(&c, req, ans);
//
//    writeLog(FILENAME, req); // log request
//    writeLog(FILENAME, ans); // log answer
//    cout << "DEBUG: Answer from server: " << ans << endl; 
//
//    // retrieve room descriptors from the answer and save them in the vector roomDescriptors
//    splitString((string)ans, roomDescriptors, ' '); 
//
//
//    // select the room
//    while (roomNumber < 0) {
//        roomNumber = selectRoom(); 
//    }
//
//          
//    //  // -----------------------------------------------------------------------
//    //  // MENU: select sensor/actuator
//    //  // -----------------------------------------------------------------------
//    //  // return here unless user choses to go 'back' to root (select room)
//    //  char sens[255] = ""; // sensor/actuator type ( temp, door, toilet/wc, window )
//    //  char strValue[255] = "";
//    //  while ( selectSensor(roomNumber,sens) != 'b' ) // select sensor ( (t)emp, (d)oor, (w)c, wi(n)dow )
//    //  {
//
//    //  // -----------------------------------------------------------------------
//    //  // MENU: select action (get, set)
//    //  // -----------------------------------------------------------------------
//    //    char action;
//    //    while ( ( action=selectAction(sens) ) != 'b' ) // get, set or configure sensor
//    //    {
//
//    //      switch ( action ) {
//    //        case 'g': // get sensor data
//    //          strcpy ( req, "get" ); 
//    //          strcpy ( strValue, "" ); // reset strValue
//    //          break;
//    //        case 's': // set actuator value
//    //          strcpy ( req, "set" ); 
//    //          value = askForValue ( sens, roomNumber );
//    //          sprintf(strValue, "%d", value);
//    //          break;
//    //        /*
//    //        case 'c': // configure sensor/actuator
//    //          strcpy ( req, "conf " ); 
//    //          break;
//    //        */
//    //        default:
//    //          break;
//    //      }
//    //  // -----------------------------------------------------------------------
//    //  // SEND: compose server query
//    //  // -----------------------------------------------------------------------
//    //      strcat ( req, " " );                                  // append space 
//    //      strcat ( req, sens );                                 // append sensor type
//    //      strcat ( req, " " );                                  // append space 
//    //      strcat ( req, roomDescriptors[roomNumber].c_str() );  // append descriptor 
//    //      if ( strValue[0] != '\0' ) { // only append space when strValue is set
//    //        strcat ( req, " " );  
//    //        strcat ( req, strValue );
//    //      }
//    //            
//    //      // send request to server and output reply
//    //      cout << "\n====================================================" << endl; 
//    //      cout << "Request string: " << req << endl;
//    //      client_send_request(&c, req, ans);
//    //      cout << "Answer from server: " << ans << endl; 
//    //      cout << "====================================================" << endl; 
//    //      cout << "\n\n";
//    //      
//    //      writeLog ( FILENAME, req ); // log request
//    //      writeLog ( FILENAME, ans ); // log answer
//    //    }
//    //  } 
//
//      roomNumber = -1; // reset room selection
//    } while (1);
//
//    cout << "Closing program." << endl;
//    return 0;
//}


int main(int argc, char* argv[]) {
    Client c(argv[1], argv[2]);
    char req[1024];
    char ans[1024];

    std::cout << "\n\n-=[ BuildingMaster FHW 3000 ]=-\n\n";
    std::cout << "(Ctrl-c to quit)\n\n" << endl;

    do {
        int room_number = -1;
        SENSOR_TYPES sensor_type;

        // get initial building configuration from server
        strcpy(req, "cfg -g");
        client_send_request(&c, req, ans);

        writeLog(FILENAME, req); // log request
        writeLog(FILENAME, ans); // log answer
        //cout << "DEBUG: Answer from server: " << ans << endl;

        // retrieve room descriptors from the answer and save them in the vector roomDescriptors
        splitString((string)ans, roomDescriptors, ' ');

        // select the room
        while (room_number < 0) {
            room_number = selectRoom();
        }

        // select the sensor type
        sensor_type = select_sensor_or_actuator();

        // select the query according to the selected sensor type
        select_query_for_chosen_sensor(room_number, sensor_type, &c, req, ans);

        // Print and log the server answer
        cout << "Answer from server: " << ans << endl;   
        cout << "\n\n";
        writeLog ( FILENAME, req ); // log request
        writeLog ( FILENAME, ans ); // log answer

        // Ask to go back to main menu
        cout << "Press any key to return to main menu." << endl;
        getKBEntry(NULL);
        cout << "\n\n\n\n\n\n\n\n\n\n\n";
    } while (1);

    cout << "Closing program." << endl;
    return 0;
}


void client_send_request(Client* client, char* request, char *answer) {
    int res = 0;
    do {
        res = client->sendRequest(request, answer);
        if (res == ERR_ABORT) {
            std::cout << "Could not reach server. Aborting program..." << std::endl;
            exit(-1);
        }
    } while (res == ERR_RETRY);
}


SENSOR_TYPES select_sensor_or_actuator() {
    char choice;

    do {
        print_select_sensor_menu();
        getKBEntry(&choice);
        /* cout << "Choice: " << choice << endl; */
        cout << "\n\n";

        switch (choice) {
        case 't':
            return SENSOR_TEMP;

        case 'd':
            return SENSOR_DOOR;

        case 'l':
            return SENSOR_TOILET;

        case 'w':
            return SENSOR_WINDOW;

        default:
            break;
        }        
    } while (1);
}


int select_query_for_chosen_sensor(int room_number, SENSOR_TYPES sensor_type, Client* client, char* request, char* answer) {
    switch (sensor_type) {
    case SENSOR_TEMP:
        return execute_query_temp(room_number, client, request, answer);

    case SENSOR_DOOR:
        return execute_query_door(room_number, client, request, answer);

    case SENSOR_TOILET:
        return execute_query_toilet(room_number, client, request, answer);

    case SENSOR_WINDOW:
        return execute_query_window(room_number, client, request, answer);

    default:
        return EXIT_FAILURE;
    }
}


int execute_query_temp(int room_number, Client* client, char* request, char* answer) {
    char choice;
    int set_value = 0;

    do {
        cout << "(g)et temperature reading" << endl;
        cout << "(s)et desired temperature" << endl;

        getKBEntry(&choice);
        cout << "\n\n";

        switch (choice) {
        case 'g':
            sprintf(request, "get temp %s", roomDescriptors[room_number].c_str());
            client_send_request(client, request, answer);
            return EXIT_SUCCESS;

        case 's':
            cout << "Set Value: ";
            set_value = getKBEntry(NULL);

            sprintf(request, "set temp %s %.2lf", roomDescriptors[room_number].c_str(), (float)set_value);
            client_send_request(client, request, answer);
            return EXIT_SUCCESS;

        default:
            break;
        }
    } while (1);
}


int execute_query_door(int room_number, Client* client, char* request, char* answer) {
    char choice;
    int set_value = 0;

    do {
        cout << "(g)et door status" << endl;
        cout << "(l)ock the door" << endl;
        cout << "(u)nlock the door" << endl;

        getKBEntry(&choice);
        cout << "\n\n";

        switch (choice) {
        case 'g':
            sprintf(request, "get door %s", roomDescriptors[room_number].c_str());
            client_send_request(client, request, answer);
            return EXIT_SUCCESS;

        case 'l':
            sprintf(request, "set door %s %i", roomDescriptors[room_number].c_str(), 1);
            client_send_request(client, request, answer);
            return EXIT_SUCCESS;

        case 'u':
            sprintf(request, "set door %s %i", roomDescriptors[room_number].c_str(), 0);
            client_send_request(client, request, answer);
            return EXIT_SUCCESS;

        default:
            break;
        }
    } while (1);
}



int execute_query_toilet(int room_number, Client* client, char* request, char* answer) {
    char choice;
    int set_value = 0;

    do {
        cout << "(g)et toilet sensor status" << endl;

        getKBEntry(&choice);
        cout << "\n\n";

        switch (choice) {
        case 'g':
            sprintf(request, "get toilet %s", roomDescriptors[room_number].c_str());
            client_send_request(client, request, answer);
            return EXIT_SUCCESS;

        default:
            break;
        }
    } while (1);
}


int execute_query_window(int room_number, Client* client, char* request, char* answer) {
    char choice;
    int set_value = 0;

    do {
        cout << "(g)et window status" << endl;
        cout << "(o)pen the windows" << endl;
        cout << "(c)lose the windows" << endl;

        getKBEntry(&choice);
        cout << "\n\n";

        switch (choice) {
        case 'g':
            sprintf(request, "get window %s", roomDescriptors[room_number].c_str());
            client_send_request(client, request, answer);
            return EXIT_SUCCESS;

        case 'o':
            sprintf(request, "set window %s %i", roomDescriptors[room_number].c_str(), 0);
            client_send_request(client, request, answer);
            return EXIT_SUCCESS;

        case 'c':
            sprintf(request, "set window %s %i", roomDescriptors[room_number].c_str(), 1);
            client_send_request(client, request, answer);
            return EXIT_SUCCESS;

        default:
            break;
        }
    } while (1);
}



//// TEST: check user valid input, empty string and zero-termination, roomID range
//int askForValue ( const char * descr, int roomID )
//{
//  // roomID out of range:
//  if ( (roomID >= roomDescriptors.size()) || (roomID < 0) ) return -1; 
//
//  // descr is empty:
//  if ( descr[0] == '\0' ) return -1;
//
//  if ( !strcmp ( descr, "door" ) ) {
//    return lockOrUnlock ( descr, roomID );
//  }
//  else 
//  { 
//    int choice;
//    // bool validChoice = false;
//    // do {
//      cout << "----------------------------------------------------" << endl;
//      cout << "Set " << descr << " for room '" << roomDescriptors[roomID] << "'" << endl;
//      cout << "----------------------------------------------------" << endl;
//      //cout << "\n\n(c)ancel" << endl; 
//      cout << "Value: ";
//      choice = getKBEntry(NULL);
//      // if ( !strcmp (choice, "c") ) return 0;
//      // validChoice = true;
//      cout << "\n\n";
//    // } while ( !validChoice ); 
//    return choice;
//  }
//}
//
//// TEST: empty string, range of roomID
//// check return value
//int lockOrUnlock ( const char * descr, int roomID )
//{
//  // roomID out of range:
//  if ( (roomID >= roomDescriptors.size()) || (roomID < 0) ) return -1; 
//
//  char choice;
//    cout << "\n\n----------------------------------------------------" << endl;
//    cout << "(l)ock or (u)nlock " << descr << " for room '" << roomDescriptors[roomID] << "'" << endl;
//    cout << "----------------------------------------------------" << endl; 
//    cout << "Choice: ";
//    getKBEntry(&choice);
//    cout << "\n\n";
//    if ( choice == 'l' ) return 1; // lock
//    else if ( choice == 'u' ) return 0; // unlock
//    else return -1; // error
// }



// TEST: check return value against input value, check out of range behaviour
// for selection
int selectRoom ( void )
{ 
  int 
    choice, 
    roomCount = (int)roomDescriptors.size();
  //cout << "Number of rooms: " << roomDescriptors.size() << endl;

  cout << "----------------------------------------------------" << endl;
  std::cout << "Please select a room \n";
  cout << "----------------------------------------------------" << endl; 
  for ( int i = 0; i < roomCount; i++ ) {
    std::cout << "(" << i << ")\t" << roomDescriptors[i] << "\n";
  }
  //cout << "\n\n(q)uit program" << endl;
  cout << "----------------------------------------------------" << endl; 
  std::cout << "Choice: (0 - " << roomCount-1 << "): ";
  choice = getKBEntry (NULL); 
  cout << "\n\n";

  if ( ( choice >= 0 ) && ( choice < roomCount ) ) return choice;
  else return -1; // wrong entry
}


void print_select_sensor_menu() {
    cout << "----------------------------------------------------" << endl;
    cout << "Please select the desired sensor or actuator" << "\n";
    cout << "----------------------------------------------------" << endl; 
    cout << "(t)emperature management" << endl;
    cout << "(d)oor access control" << endl;
    cout << "(l)avatory management" << endl;
    cout << "(w)indow control" << endl;
    //cout << "\n\n(b)ack" << endl;
    cout << "----------------------------------------------------" << endl; 
    cout << "Choice: ";
}

//// TEST: range of room ID
//char selectSensor ( int room, char * sens )
//{
//  char choice;
//  bool decided = false;
//  
//  // roomID out of range:
//  if ( (room >= roomDescriptors.size()) || (room < 0) ) return -1; 
//
//  do { 
//      print_select_sensor_menu();
//    getKBEntry (&choice);
//    /* cout << "Choice: " << choice << endl; */
//    cout << "\n\n";
//
//    switch (choice) {
//      case 't': 
//        strcpy ( sens, "temp" );
//        decided = true;
//        break;
//      case 'd':
//        strcpy ( sens, "door" );
//        decided = true;
//        break;
//      case 'w':
//        strcpy ( sens, "toilet" );
//        decided = true;
//        break; 
//      case 'n':
//        strcpy ( sens, "window" );
//        decided = true;
//        break; 
//      case 'b':
//        decided = true;
//        break;
//    } 
//  } while (!decided); 
//
//  cout << "\n\n";
//
//  return choice; 
//}

//// TEST: empty string
//char selectAction ( const char * descr )
//{
//  char choice;
//  bool decided = false;
//
//  do {
//    cout << "----------------------------------------------------" << endl;
//    std::cout << "Select action for '"<< descr << "'" << endl;
//    cout << "----------------------------------------------------" << endl; 
//    cout << "(g)et sensor data" << endl;
//    cout << "(s)et actuator" << endl;
//    // cout << "(c)onfigure sensor/actuator" << endl;
//    cout << "\n\n(b)ack" << endl;
//    cout << "----------------------------------------------------" << endl; 
//    std::cout << "Choice: ";
//    getKBEntry (&choice);
//    cout << "\n\n";
//
//    switch ( choice ) {
//      case 'g':
//      case 's':
//      case 'b':
//        decided = true;
//        break; 
//      default: 
//        decided = false;
//        break;
//    }
//  } while (!decided);
//
//  return choice; 
//}

// write client-server communication to logfile
int writeLog ( const char * filename, const char * message )
{
  // FOR FILE HANDLING REFER TO http://www.cplusplus.com/doc/tutorial/files/
  fstream logfile(filename); // opens file if file exists, does not create new file if file doesn't exist

  // check if logfile exists
  if (!logfile.good()) {
    cout << "Config file does not exist" << endl;

    // if file does not exist, create new file
    logfile.open(filename, ios::out | ios::trunc);    // this is what creates the new file
    if (logfile.is_open()) {
      cout << "Created new config file!\n";
    } else {
      cout << "Could not create config file!\n";
      return -1;
    }
  } 
  logfile.close();

  // write to existing logfile

  logfile.open(filename, std::ios_base::app);
  if (logfile.is_open()) {
    
    time_t now = time(0); // current date/time based on current system
    tm *ltm = localtime(&now);
    // insert date
    logfile << "\n" << 1900 + ltm->tm_year << "-" << 1 + ltm->tm_mon << "-" << ltm->tm_mday;
    // insert timestamp
    logfile << " " << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec; 
    // insert message
    logfile << " " << message;
    logfile.close();
  } else {
    cout << "Could not write to existing config file!\n";
    return -1;
  }

  return 0;
}

// returns user input (changes behavior for UNITTEST)
int getKBEntry ( char * kbentry )
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
    string s_choice;
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
int splitString ( const std::string &txt, std::vector<std::string> &strs, char ch )
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


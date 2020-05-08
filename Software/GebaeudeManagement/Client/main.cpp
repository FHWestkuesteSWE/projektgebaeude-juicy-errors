// main.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms :).


#include <signal.h>
#include <iostream>
#include <string>
#include "BasicClient.h"
#include "main.h"

using namespace std;
int main(int argc, char* argv[]) 
{
    BasicClient c(argv[1], argv[2]);
    char req[1024];
    char ans[1024];
    char choice;
    int numRooms = 0; // number of configured rooms

    int roomNumber = -1;
    int roomAction = 0; // either GET_VALUE or SET_VALUE
    int value = 0; // set value 
    
    std::cout << "\n\n-=[ BuildingMaster FHW 3000 ]=-\n\n";
    std::cout << "(Ctrl-c to quit)\n\n" << endl;

    do {
      // -----------------------------------------------------------------------
      // MENU: select room (root)
      // -----------------------------------------------------------------------
      // get building configuration (room descriptors) from server
      strcpy(req, "cfg -g");
      cout << "DEBUG: Request string: " << req << endl;
      c.sendRequest(req, ans);
      //strcpy ( ans, "living1 living2 kitchen1 lavatory1 garden1 garage1 patio1" ); // because server doesn't use delimiters yet
      cout << "DEBUG: Answer from server: " << ans << endl; 
      numRooms = splitString ( (string)ans, roomDescriptors, ' ' ); // split string into vector of strings
      // for ( int i = 0; i < numRooms; i ++ ) cout << roomDescriptors[i] << endl;
      // ---

      while ( roomNumber < 0 ) roomNumber = selectRoom ( numRooms ); 
      
      // -----------------------------------------------------------------------
      // MENU: select sensor/actuator
      // -----------------------------------------------------------------------
      // return here unless user choses to go 'back' to root (select room)
      char sens[255] = ""; // sensor/actuator type ( temp, door, toilet/wc )
      char strValue[255];
      while ( selectSensor(roomNumber,sens) != 'b' ) // select sensor ( (t)emp, (d)oor, (w)c )
      {

      // -----------------------------------------------------------------------
      // MENU: select action (get, set)
      // -----------------------------------------------------------------------
        char action;
        while ( ( action=selectAction(sens) ) != 'b' ) // get, set or configure sensor
        {

          switch ( action ) {
            case 'g': // get sensor data
              strcpy ( req, "get" ); 
              strcpy ( strValue, "" ); // reset strValue
              break;
            case 's': // set actuator value
              strcpy ( req, "set" ); 
              value = askForValue ( sens, roomNumber );
              sprintf(strValue, "%d", value);
              break;
            /*
            case 'c': // configure sensor/actuator
              strcpy ( req, "conf " ); 
              break;
            */
            default:
              break;
          }
      // -----------------------------------------------------------------------
      // SEND: compose server query
      // -----------------------------------------------------------------------
          strcat ( req, " " );                                  // append space 
          strcat ( req, sens );                                 // append sensor type
          strcat ( req, " " );                                  // append space 
          strcat ( req, roomDescriptors[roomNumber].c_str() );  // append descriptor 
          if ( strValue[0] != '\0' ) { // only append space when strValue is set
            strcat ( req, " " );  
            strcat ( req, strValue );
          }
                
          // send request to server and output reply
          cout << "\n====================================================" << endl; 
          cout << "Request string: " << req << endl;
          c.sendRequest(req, ans);
          cout << "Answer from server: " << ans << endl; 
          cout << "====================================================" << endl; 
          cout << "\n\n";
        }
      } 

      roomNumber = -1; // reset room selection
    } while (1);

    cout << "Closing program" << endl;
    return 0;
}

// TEST: check user valid input, empty string and zero-termination, roomID range
int askForValue ( const char * descr, int roomID )
{
  if ( !strcmp ( descr, "door" ) ) {
    return lockOrUnlock ( descr, roomID );
  }
  else 
  { 
    int choice;
    bool validChoice = false;
    do {
      cout << "----------------------------------------------------" << endl;
      cout << "Set " << descr << " for room '" << roomDescriptors[roomID] << "'" << endl;
      cout << "----------------------------------------------------" << endl;
      //cout << "\n\n(c)ancel" << endl; 
      cout << "Value: ";
      cin >> choice; 
      // if ( !strcmp (choice, "c") ) return 0;
      validChoice = true;
      cout << "\n\n";
    } while ( !validChoice ); 
    return choice;
  }
}

// TEST: empty string, zero-termination, range of roomID
// check return value
int lockOrUnlock ( const char * descr, int roomID )
{
  char choice;
    cout << "\n\n----------------------------------------------------" << endl;
    cout << "(l)ock or (u)nlock " << descr << " for room '" << roomDescriptors[roomID] << "'" << endl;
    cout << "----------------------------------------------------" << endl; 
    cout << "Choice: ";
    cin >> choice; 
    cout << "\n\n";
    if ( choice == 'l' ) return 1; // lock
    else if ( choice == 'u' ) return 0; // unlock
    else return -1; // error
 }

// TEST: check range roomCount, check return value
int selectRoom ( int roomCount )
{
  int choice;

  cout << "----------------------------------------------------" << endl;
  std::cout << "\nSelect room \n";
  cout << "----------------------------------------------------" << endl; 
  for ( int i = 0; i < roomCount; i++ ) {
    std::cout << "(" << i << ")\t" << roomDescriptors[i] << "\n";
  }
  //cout << "\n\n(q)uit program" << endl;
  cout << "----------------------------------------------------" << endl; 
  std::cout << "Choice: (0 - " << roomCount << "): ";
  cin >> choice;
  cout << "\n\n";
  if ( ( choice >= 0 ) && ( choice < roomCount ) ) return choice;
  else return -1; // wrong entry
}


char selectSensor ( int room, char * sens )
{
  char choice;
  bool decided = false;

  do { 
    cout << "----------------------------------------------------" << endl;
    cout << "Select sensor/actuator in room '" << roomDescriptors[room] << "'\n";
    cout << "----------------------------------------------------" << endl; 
    cout << "(t)emperature sensor" << endl;
    cout << "(d)oor sensor/actuator" << endl;
    cout << "(w)c/toilet sensor" << endl;
    cout << "\n\n(b)ack" << endl;
    cout << "----------------------------------------------------" << endl; 
    cout << "Choice: ";
    cin >> choice;
    cout << "\n\n";

    switch (choice) {
      case 't': 
        strcpy ( sens, "temp" );
        decided = true;
        break;
      case 'd':
        strcpy ( sens, "door" );
        decided = true;
        break;
      case 'w':
        strcpy ( sens, "toilet" );
        decided = true;
        break; 
      case 'b':
        decided = true;
        break;
    } 
  } while (!decided);

  cout << "\n\n";
  return choice; 
}


char selectAction ( const char * descr )
{
  char choice;
  bool decided = false;

  do {
    cout << "----------------------------------------------------" << endl;
    std::cout << "Select action for '"<< descr << "'" << endl;
    cout << "----------------------------------------------------" << endl; 
    cout << "(g)et sensor data" << endl;
    cout << "(s)et actuator" << endl;
    // cout << "(c)onfigure sensor/actuator" << endl;
    cout << "\n\n(b)ack" << endl;
    cout << "----------------------------------------------------" << endl; 
    std::cout << "Choice: ";
    cin >> choice;
    cout << "\n\n";

    switch ( choice ) {
      case 'g':
      case 's':
      case 'b':
        decided = true;
        break; 
      default: 
        decided = false;
        break;
    }
  } while (!decided);

  return choice; 
}


size_t splitString ( const std::string &txt, std::vector<std::string> &strs, char ch )
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
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}


#if 0
void getTempMenu(void)
{

    std::cout << "\nPlease choose room descriptor of the following: \n";
    std::cout << "\tlivingRoom \t\t(1)\n";
    std::cout << "\tkitchen \t\t(2)\n";
    std::cout << "\ttoiletRoom1 \t\t(3)\n\n";
    std::cout << "Exit \t\t\t\t(0)\n";
    std::cout << "------------------------------------\n";

    std::cout << "Please enter an integer value (0-3): \n";

}

void mainMenu(void)
{
    int userInput = -1;
    while (userInput < 0 || userInput > 5) {
        std::cout << "Building management system FHW 3000\n";
        std::cout << "------------------------------------\n";
        std::cout << "What do you want to do?\n";
        std::cout << "------------------------------------\n";
        std::cout << "Get current room temperature \t(1)\n";
        std::cout << "Set current room temperature \t(2)\n\n";

        std::cout << "Get current door status \t(3)\n";
        std::cout << "Set current door status \t(4)\n\n";

        std::cout << "Get current toilet status \t(5)\n\n";
        std::cout << "Exit \t\t\t\t(0)\n\n";

        std::cout << "------------------------------------\n";

        std::cout << "Please enter an integer value (0-5): ";
        std::cin >> userInput;
    }
    switch (userInput)
    {
    case 1:
        getTempMenu();
    default:
        break;
    }
}

// felix's get/set config from server
  char choice;
  char descr[12];
  cout << "(g)et or (u)pdate config " << "?" << endl;
  cout << "\n\n(c)ancel" << endl;
  cout << "----------------------------------------------------" << endl;
  cout << "Choice: ";
  cin >> choice;

  switch (choice) {
  case 'g':
      strcpy(req, "cfg -g");
      break;
  case 'u':
      strcpy(req, "cfg -u");
      break;
  case 'a':
      cout << "Enter room descriptor: ";
      cin >> descr;
      strcpy(req, "cfg -a ");
      strcat(req, descr);
      break;
  case 'd':
      cout << "Enter room descriptor: ";
      cin >> descr;
      strcpy(req, "cfg -d ");
      strcat(req, descr);
      break;
  default:
      break;
  }
  cout << "Request string: " << req << endl;
  c.sendRequest(req, ans);
  cout << "Answer from server: " << ans << endl;
  break;
#endif

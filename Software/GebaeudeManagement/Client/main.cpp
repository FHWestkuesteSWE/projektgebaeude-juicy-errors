// main.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.


#include <iostream>
#include <string>
#include "BasicClient.h"
#include "main.h"

using namespace std;
int main(int argc, char* argv[]) {
    BasicClient c(argv[1], argv[2]);
    char req[1024];
    char ans[1024];
    char wahl;
    int roomNumber = 0;
    int roomAction = 0; // either GET_VALUE or SET_VALUE
    int value = 0; // set value

    do {
        std::cout << "\n\n-=[ BuildingMaster FHW 3000 ]=-\n\n";
        cout << "Main Menu" << endl;
        cout << "----------------------------------------------------" << endl;
        cout << "Room temperature         \t(t)" << endl; // user story A, B, D
        cout << "Outer doors              \t(d)" << endl; // user story C
        cout << "Toilet status            \t(w)" << endl; // user story C
        cout << "\n\n" << endl;
        cout << "Quit program             \t(q)" << endl;
        cout << "----------------------------------------------------" << endl;
        cout << "Choice: ";
        cin >> wahl;

        switch (wahl) {
            case 't': // Room temperature
            // -------------------------------------------------------------------- 
                // ask for room descriptor
                roomNumber = whichRoom();
                roomAction = 0; // either GET_VALUE or SET_VALUE
                value = 0; // set value
                while ( !roomAction ) roomAction = getOrSet ("temperature"); // ask for get or set 

                if ( roomAction == GET_VALUE ) { // get temperature
                strcpy ( req, "get Temp " );
                strcat ( req, roomDescriptors[roomNumber] ); // add room descriptor
                }
                else if ( roomAction == SET_VALUE ) { // set temperature
                value = askForValue ( "temperature", roomNumber, 14, 42 ); 
                strcpy ( req, "set Temp " );
                strcat ( req, roomDescriptors[roomNumber] ); // add room descriptor
                strcat ( req, " " );
                char strValue[10];
                sprintf(strValue, "%d", value);
                strcat ( req, strValue ); // add temperature value
                }

                // send request to server and output reply
                cout << "Request string: " << req << endl;
                c.sendRequest(req, ans);
                cout << "Answer from server: " << ans << endl;
                break;
            // -------------------------------------------------------------------- 

            case 'd': // Outer doors
            // -------------------------------------------------------------------- 
                // ask for room descriptor
                roomNumber = whichRoom();
                roomAction = 0; // either GET_VALUE or SET_VALUE
                value = 0; // set value
                while ( !roomAction ) roomAction = getOrSet ("outer doors"); // ask for get or set 

                if ( roomAction == GET_VALUE ) { // get room door status
                strcpy ( req, "get Door " );
                strcat ( req, roomDescriptors[roomNumber] ); // add room descriptor

                } else if ( roomAction == SET_VALUE ) { // set room door (lock or unlock)
                value = -1;

                while ( value == -1) value = lockOrUnlock ( "outer doors", roomNumber ); 
                strcpy ( req, "set Door " );
                strcat ( req, roomDescriptors[roomNumber] ); // add room descriptor
                strcat ( req, " " );
                char strValue[10];
                sprintf(strValue, "%d", value);
                strcat ( req, strValue ); // add boolen value for lock (1) or unlock (0)
                }

                // send request to server and output reply
                cout << "Request string: " << req << endl;
                c.sendRequest(req, ans);
                cout << "Answer from server: " << ans << endl;
                break;
            // -------------------------------------------------------------------- 

            case 'w': // get toilet status
            // -------------------------------------------------------------------- 
                // ask for room descriptor
                roomNumber = whichRoom();
                roomAction = 0; // either GET_VALUE or SET_VALUE
                value = 0; // set value
                strcpy ( req, "get Toilet " );
                strcat ( req, roomDescriptors[roomNumber] ); // add room descriptor

                value = askForValue ( "toilet number", roomNumber, 0, 6 ); 
                strcpy ( req, "get Toilet " );
                strcat ( req, roomDescriptors[roomNumber] ); // add room descriptor
                strcat ( req, " " );
                char strValue[10];
                sprintf(strValue, "%d", value);
                strcat ( req, strValue ); // add value for toilet number

                // send request to server and output reply
                cout << "Request string: " << req << endl;
                c.sendRequest(req, ans);
                cout << "Answer from server: " << ans << endl;
                break;
            // -------------------------------------------------------------------- 

            case 'q':
                break;

            case 'c':
                strcpy(req, "cfg");
                cout << "Request string: " << req << endl;
                c.sendRequest(req, ans);
                cout << "Answer from server: " << ans << endl;
                break;

            default:
                cout << "I'm sorry Dave, I can't do that." << endl;
                break;
        }           
    } while (wahl != 'q');

    cout << "Closing program" << endl;
    return 0;
}

int getOrSet ( const char * descr )
{
  char choice;
  cout << "\n\n----------------------------------------------------" << endl;
  cout << "(g)et or (s)et " << descr << "?" << endl;
  cout << "\n\n(c)ancel" << endl; 
  cout << "----------------------------------------------------" << endl; 
  cout << "Choice: ";
  cin >> choice;

  switch (choice) {
    case 'g':
      return GET_VALUE;
      break;
    case 's':
      return SET_VALUE;
      break;
    case 'c':
    default:
      return 0;
      break;
  }
}

int askForValue ( const char * descr, int roomID, int dim_low, int dim_high )
{
  char choice[3];
  int intChoice;
  bool validChoice = false;
  do {
    cout << "\n\n----------------------------------------------------" << endl;
    cout << "Set " << descr << " for room '" << roomDescriptors[roomID] << "'" << endl;
    cout << "\n\n(c)ancel" << endl; 
    cout << "----------------------------------------------------" << endl; 
    cout << "Please enter value (" << dim_low << " to " << dim_high << " ): ";
    cin >> choice; 
    if ( !strcmp (choice, "c") ) return 0;
    intChoice = strtol( choice, (char **)NULL, 10 );
    if ( intChoice <= dim_high && intChoice >= dim_low ) validChoice = true;
  } while ( !validChoice );

  return intChoice;
}

int lockOrUnlock ( const char * descr, int roomID )
{
  char choice;
    cout << "\n\n----------------------------------------------------" << endl;
    cout << "(l)ock or (u)nlock " << descr << " for room '" << roomDescriptors[roomID] << "'" << endl;
    cout << "\n\n(c)ancel" << endl; 
    cout << "----------------------------------------------------" << endl; 
    cout << "Choice: ";
    cin >> choice; 
    if ( choice == 'l' ) return 1; // lock
    else if ( choice == 'u' ) return 1; // unlock
    else return -1; // error
 }

int whichRoom (void)
{
  int choice;

  cout << "\n\n----------------------------------------------------" << endl;
  std::cout << "\nPlease choose room descriptor: \n";
  for ( int i = 0; i < NUM_ROOMS; i++ ) {
    std::cout << "\t" << roomDescriptors[i] << "\t\t" << "(" << i + 1 << ")\n";
  }
  std::cout << "\n\nExit \t\t\t\t(0)\n";
  cout << "----------------------------------------------------" << endl; 
  std::cout << "Choice (0 - " << NUM_ROOMS << "):";
  cin >> choice;

  return choice - 1;
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
#endif

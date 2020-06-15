// main.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms :).

//#define UNITTEST

#include "main.h"

/* #include "../Server/FileHandling.h" */

#ifdef UNITTEST
  int kbRetVal = 42; // default integer return value for keyboard entry
  char kbRetValCh = 'f'; // default char return value for keyboard entry
#endif

using namespace std;

int main(int argc, char* argv[]) 
{
    Client c(argv[1], argv[2]);

    std::cout << "\n\n-=[ BuildingMaster FHW 3000 ]=-\n\n";
    std::cout << "(Ctrl-c to quit)\n\n" << endl;

    do {
        int room_number = -1;
        //SENSOR_TYPES sensor_type;

        writeLog ( FILENAME, c.getStrReq()) ; // log request
        writeLog ( FILENAME, c.getStrAns()) ; // log answer
        //cout << "DEBUG: Answer from server: " << ans << endl;


        // select the room
        while (room_number < 0) {
            room_number = c.selectRoom();
        }

        // select the sensor type
        //sensor_type = 
          c.select_sensor_or_actuator(room_number);

        // select the query according to the selected sensor type
        //c.select_query_for_chosen_sensor(room_number, sensor_type, req, ans);

        // Print and log the server answer
        //cout << "Request for server: " << c.getStrReq() << endl;   
        cout << "Answer from server: " << c.getStrAns() << endl;   
        cout << "\n\n";
        writeLog ( FILENAME, c.getStrReq() ); // log request
        writeLog ( FILENAME, c.getStrAns() ); // log answer

        // Ask to go back to main menu
        cout << "Returning to main menu." << endl;
        system("pause"); // wait for key press
        cout << "\n\n\n\n\n\n\n\n\n\n\n";
    } while (1);

    cout << "Closing program." << endl;
    return 0;
}


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


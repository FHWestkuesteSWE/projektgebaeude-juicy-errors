// main.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
// Test commit
// Test commit Soeren

#include <iostream>
#include "BasicClient.h"

using namespace std;
int main(int argc, char* argv[])
{
    BasicClient c(argv[1], argv[2]);
    char req[1024] = "GET TEMP 1";
    char ans[1024];
    char wahl;
    do {
        std::cout << "Gebauedeleitsystem FHW 3000\n";
        cout << "Was wollen Sie tun: " << endl;
        cout << "----------------------------------------------------" << endl;
        cout << "Aktuelle Raumtemperatur ueberpruefen \t(t)" << endl;
        cout << "Aussentueren oeffnen / schliessen \t(a)" << endl;
        cout << "..." << endl;
        cout << "Beenden \t\t\t\t(e)" << endl;
        cout << "----------------------------------------------------" << endl;
        cout << "Ihre Wahl: ";
        cin >> wahl;
        switch (wahl) {
        case 't': // req zusammenbauen
            c.sendRequest(req, ans);
            cout << ans;
            break;
        default:;
            cout << "No valid entry" << endl;
        }
    } while (wahl != 'e');

    cout << "Closing program" << endl;
    return 0;
}


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

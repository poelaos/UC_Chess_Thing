#include <iostream>
#include "GameState.h"
#include "GameLogic.h"

using namespace std;

int main(){

    showMenu();

    int menuSelect;

    do {
        std::cin >> menuSelect;
        switch(menuSelect) {
            case 1:
                //initiate game with Another human player
                system("clear");
                pvp();
                break;
            case 2:
                //initiate game with weak computer
                system("clear");
               //function for weak comp gamemode;
                break;
            case 3:
                // initiate game with sophisticated computer
                system("clear");
                //function for sophisticated ai;
                break;
            case 4:
                //exit game/program
                system("clear");
                std::cout << "EXITING..." << std::endl;
                abort();
                break;
            default:    
                std::cout << "Choose an option 1-4." << std::endl;
        }
    } while (menuSelect !=4);
   


    
    
    
    
    return 0;
}

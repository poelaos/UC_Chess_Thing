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
                pve();
                system("clear");
                break;
            case 3:
                // initiate game with sophisticated computer
                system("clear");
                break;
            case 4:
                //display scoreboard
                system("clear");
                showScoreboard();
                break;
            case 5:
                //clear scoreboard
                system("clear");
                resetScoreboard();
                sleep(1);
                system("clear");
                showMenu();
                break;
            case 6:
                //exit game/program
                system("clear");
                std::cout << "EXITING..." << std::endl;
                abort();
                break;
            case 0:
                system("clear");
                showMenu();
                break;
            default:    
                std::cout << "Choose an option 1-4." << std::endl;
        }
    } while (menuSelect !=6);
   


    
    
    
    
    return 0;
}

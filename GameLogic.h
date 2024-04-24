#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H


#include <iostream>
#include <cstdlib>
#include "GameState.h"

void ticTacToe_Multi (int tttInteger) {
    int gameInteger;
    gameInteger = tttInteger;
    while (gameInteger == 0) {
        GameState game;
        int input1 = -1;
        int input2 = -1;
        bool validMove;

        while (game.done == false) {
            validMove = true;
            std::cin >> input1;
            std::cin >> input2;
            if (game.play(input1,input2) == false) {
                validMove == false;
                
            }
            std::system("clear");
            std::cout << game << std::endl;
            if (validMove == false) {
                std::cout << "Please enter a valid empty space with values between 0 and 2." << std::endl;
            }
        }
        if (game.hasWon(0) == true) {
            std::cout << "Player X has won!" << std::endl;
        }
        if (game.hasWon(1) == true) {
            std::cout << "Player O has won!" << std::endl;
        }
        if (game.hasWon(0) == false && game.hasWon(1) == false) {
            std::cout << "It's a draw!" << std::endl;
        }
        std::cout << "Play again? (y = 0, n = 1)" << std::endl;
        std::cin >> gameInteger;
        std::system("clear");
    }
}

void ticTacToe_AI (int tttInteger) {
    int gameInteger;
    gameInteger = tttInteger;
    while (gameInteger == 0) {
        GameState game;
        int input1 = -1;
        int input2 = -1;
        bool validMove;

        while (game.done == false) {
            validMove = true;
            std::cin >> input1;
            std::cin >> input2;
            if (game.play(input1,input2) == false) {
                validMove == false;
                
            }
            std::system("clear");
            std::cout << game << std::endl;
            if (validMove == false) {
                std::cout << "Please enter a valid empty space with values between 0 and 2." << std::endl;
            }
        }
        if (game.hasWon(0) == true) {
            std::cout << "Player X has won!" << std::endl;
        }
        if (game.hasWon(1) == true) {
            std::cout << "Player O has won!" << std::endl;
        }
        if (game.hasWon(0) == false && game.hasWon(1) == false) {
            std::cout << "It's a draw!" << std::endl;
        }
        std::cout << "Play again? (y = 0, n = 1)" << std::endl;
        std::cin >> gameInteger;
        std::system("clear");
    }
}


void menuPrinter (int remote) {
    if (remote == 0) {
        std::cout << "Welcome to Tic Tae Toe! Enter an option to begin." << std::endl;
        std::cout << "1. Singleplayer" << std::endl;
        std::cout << "2. Multiplayer" << std::endl;
        std::cout << "3. Quit" << std::endl;
    }
    if (remote == 1) {
        ticTacToe_AI(0)
    }

    if (remote == 2) {
        ticTacToe_Multi(0);
    }
}



void ultimateGameFunction (int programState) {
    while (programState != 3) {
        std::system("clear");
        menuPrinter(0);
        std::cin >> programState;
        if (programState == 1 || programState == 2) {
            std::system("clear");
            menuPrinter(programState);
        }
    }
}

#endif

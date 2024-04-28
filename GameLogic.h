#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H


#include <iostream>
#include <cstdlib>
#include "GameState.h"

#include <fstream>

#define RESET "\033[0m"
#define BLUE "\033[94m"
#define RED "\033[91m"

struct Stats {
    std::string name;
    int points;
    char symbol;

    Stats (std::string name, int points, char symbol) {
        this->name = name;
        this-> points = points;
        this->symbol = symbol;
    }

};

void saveStats(Stats& stats) {
    std::ofstream file;
    file.open("stats.txt", std::ios::app);
     if (file.is_open()) {
        file << stats.name << " " << stats.points << " " << stats.symbol;
        file.close();
    } else {
        std::cerr << "Could not open stats.txt" << std::endl;
    }
}

void showScoreboard() {
    std::ifstream file;
    file.open("stats.txt", std::ios::in);
    if (file.is_open()) {
        std::string name;
        int points;
        char symbol;
        while (file >> name >> points >> symbol) {
            std::cout << "Name: " << name << "  Points: " << points << " Symbol: " << symbol << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Could not open stats.txt" << std::endl;
    }
    std::cout << "Enter 0 to continue: " << std::endl;

}

void resetScoreboard() {
    std::ofstream file;
    file.open("stats.txt", std::ios::trunc);
    if (file.is_open()) {
        std::cout << "Scoreboard cleared!" << std::endl;
        file.close();
    } else {
        std::cerr << "Could not open stats.txt" << std::endl;
    }
}

void showMenu() {
    std::cout << 
    "Play Against:" << std::endl <<
    "  1.) Another Person " << std::endl <<
    "  2.) Weak Computer " << std::endl <<
    "  3.) Sophisticted Computer " << std::endl <<
    "  4.) Scoreboard" << std::endl <<
    "  5.) Reset scoreboard" << std::endl <<
    "  6.) Exit. " << std::endl;
}


void pvp() {

    GameState game;
    while(!game.done) {

        std::cout << game << std::endl;
        int row, col;
        bool validMove = false;

        while (!validMove) {
            std::cout << "Player 1: ";
            std::cin >> row >> col;
            if (game.play(row, col)) {
                game.play(row, col);
                system("clear");
                std::cout << game << std::endl;
                break;
            } else {
                std::cout << bold(red("Invalid Move! Try again")) << std::endl;
            }
        }

        if (game.hasWon(0)) {
            char winnerSymbol = 'X';
            std::string winnerName;
            std::cout << bold(red("Player 1 wins!")) << std::endl;
            std::cout << "Enter your name: ";
            std::cin >> winnerName;
            Stats winner(winnerName, game.turnCount, winnerSymbol);
            saveStats(winner);
            system("clear");
            showMenu();
            break;
        }

        validMove = false;

        if (game.done == true && !game.hasWon(0) && !game.hasWon(1)) {
            std::cout << "Draw!" << std::endl;
            break;
        }

        while (!validMove) {
            std::cout << "Player 2: ";
            std::cin >> row >> col;
            if (game.play(row, col)) {
                game.play(row, col);
                system("clear");
                break;
            } else {
                std::cout << bold(red("Invalid Move! Try again")) << std::endl;
            }
        }

        if (game.hasWon(1)) {
            char winnerSymbol = 'O';
            std::string winnerName;
            std::cout << game << std::endl;
            std::cout << bold(blue("Player 2 wins!")) << std::endl;
            std::cout << "Enter your name: ";
            std::cin >> winnerName;
            Stats winner(winnerName, game.turnCount, winnerSymbol);
            saveStats(winner);
            system("clear");
            showMenu();
            break;
        }
        
        if (game.done == true && !game.hasWon(0) && !game.hasWon(1)) {
            std::cout << "Draw!" << std::endl;
        }
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

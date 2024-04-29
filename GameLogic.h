#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H


#include <iostream>
#include <cstdlib>
#include <thread>  
#include <chrono> 
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
            std::cout << bold(red("Player X wins!")) << std::endl;
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
            std::cout << bold(blue("Player O wins!")) << std::endl;
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
    int gameInteger = tttInteger;
    while (gameInteger == 0) {
        GameState game;
        int input1, input2;
        bool validMove;

        while (!game.done) {
            std::system("clear");
            std::cout << game << std::endl;  

            if (game.currentTurn == 0) {  // Player's turn
                validMove = false;
                while (!validMove) {
                    std::cout << "Your turn. Enter row and column numbers (0-2): ";
                    if (!(std::cin >> input1 >> input2)) {
                        std::cin.clear();  
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  
                        std::cout << "Invalid input. Please enter numbers only." << std::endl;
                        continue;  
                    }
                    std::cout << "Input received: " << input1 << ", " << input2 << std::endl; 
                    if (game.play(input1, input2)) {
                        validMove = true;
                    } else {
                        std::cout << "Invalid move. Please try again." << std::endl;
                    }
                }
            } else {  // AI's turn
                validMove = false;
                while (!validMove) {
                    input1 = std::rand() % 3;  
                    input2 = std::rand() % 3;  
                    if (game.play(input1, input2)) {
                        validMove = true;
                        std::cout << "AI played (" << input1 << ", " << input2 << ")" << std::endl;
                    }
                }
            }
        }

        // Determine the outcome of the game
        if (game.hasWon(0)) {
            char winnerSymbol = 'X';
            std::string winnerName;
            std::cout << bold(red("Player X has won!")) << std::endl;
            std::cout << "Enter your name: ";
            std::cin >> winnerName;
            Stats winner(winnerName, game.turnCount, winnerSymbol);
            saveStats(winner);
        } else if (game.hasWon(1)) {
            std::cout << "Player O has won!" << std::endl;
        } else {
            std::cout << "It's a draw!" << std::endl;
        }

        std::cout << "Play again? (y = 0, n = 1)" << std::endl;
        std::cin >> gameInteger;
        std::system("clear");
       
    }
}
void pve(){
    ticTacToe_AI(0);
}

Vec findStrategicMove(GameState& game) {
    // Priority 1: If AI can win in the next move
    for (int i = 0; i < game.size; i++) {
        for (int j = 0; j < game.size; j++) {
            if (game.grid[i][j] == -1) {
                game.grid[i][j] = 1;
                if (game.hasWon(1)) {
                    game.grid[i][j] = -1;
                    return Vec(i, j);
                }
                game.grid[i][j] = -1;
            }
        }
    }

    // Priority 2: Block the opponent's winning move
    for (int i = 0; i < game.size; i++) {
        for (int j = 0; j < game.size; j++) {
            if (game.grid[i][j] == -1) {
                game.grid[i][j] = 0;
                if (game.hasWon(0)) {
                    game.grid[i][j] = -1;
                    return Vec(i, j);
                }
                game.grid[i][j] = -1;
            }
        }
    }

    // Priority 3: Take the center if available
    if (game.size % 2 == 1) { 
        int center = game.size / 2;
        if (game.grid[center][center] == -1) {
            return Vec(center, center);
        }
    }

    // Fallback: Play the first available spot
    for (int i = 0; i < game.size; i++) {
        for (int j = 0; j < game.size; j++) {
            if (game.grid[i][j] == -1) {
                return Vec(i, j);
            }
        }
    }

    return Vec(-1, -1); 
}

bool isBoardFull(GameState& game) {
    for (int i = 0; i < game.size; i++) {
        for (int j = 0; j < game.size; j++) {
            if (game.grid[i][j] == -1) {
                return false;
            }
        }
    }
    return true;
}

void unbeatable_AI(int tttInteger) {
    int gameInteger = tttInteger;
    while (gameInteger == 0) {
        GameState game;
        int input1, input2;
        bool validMove;

        while (!game.done) {
            std::system("clear");
            std::cout << game << std::endl;  

            if (game.currentTurn == 0) {  // Player's turn
                validMove = false;
                while (!validMove) {
                    std::cout << "Your turn. Enter row and column numbers (0-" << game.size - 1 << "): ";
                    if (!(std::cin >> input1 >> input2)) {
                        std::cin.clear();  
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid input. Please enter numbers only." << std::endl;
                        continue;
                    }
                    if (input1 >= 0 && input1 < game.size && input2 >= 0 && input2 < game.size) {
                        if (game.play(input1, input2)) {
                            validMove = true;
                        } else {
                            std::cout << "Invalid move. This spot is already taken. Please try again." << std::endl;
                        }
                    } else {
                        std::cout << "Input out of bounds. Please try again." << std::endl;
                    }
                }
            }

            
            if (game.hasWon(0)) {
                std::cout << "Player X has won!" << std::endl;
                break;
            }

            if (isBoardFull(game)) {
                std::cout << "It's a draw!" << std::endl;
                break;
            }

            // AI's turn
            if (game.currentTurn == 1) {
                Vec bestMove = findStrategicMove(game);
                game.play(bestMove.x, bestMove.y);
                std::cout << "AI plays: " << bestMove << std::endl;

                if (game.hasWon(1)) {
                    std::cout << "Player O has won!" << std::endl;
                    break;
                }

                if (isBoardFull(game)) {
                    std::cout << "It's a draw!" << std::endl;
                    break;
                }
            }
        }

        std::cout << "Play again? (y = 0, n = 1)" << std::endl;
        std::cin >> gameInteger;
        std::system("clear");
    }
}

void pveHard(){
    unbeatable_AI(0);
}

#endif




EXPIRIMENTAL CHANGES BEGIN HERE, COPY AND PASTE THIS SECTION IF YOU ONLY WANT THE EXPERIMENT CHANGES:
#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H


#include <iostream>
#include <cstdlib>
#include <thread>  
#include <chrono> 
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
            std::cout << bold(red("Player X wins!")) << std::endl;
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
            std::cout << bold(blue("Player O wins!")) << std::endl;
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

void weak_AI (int tttInteger) {
    int gameInteger = tttInteger;
    while (gameInteger == 0) {
        GameState game;
        int input1, input2;
        bool validMove;

        while (!game.done) {
            std::system("clear");
            std::cout << game << std::endl;  

            if (game.currentTurn == 0) {  // Player's turn
                validMove = false;
                while (!validMove) {
                    std::cout << "Your turn. Enter row and column numbers (0-2): ";
                    if (!(std::cin >> input1 >> input2)) {
                        std::cin.clear();  
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  
                        std::cout << "Invalid input. Please enter numbers only." << std::endl;
                        continue;  
                    }
                    std::cout << "Input received: " << input1 << ", " << input2 << std::endl; 
                    if (game.play(input1, input2)) {
                        validMove = true;
                    } else {
                        std::cout << "Invalid move. Please try again." << std::endl;
                    }
                }
            } else {  // AI's turn
                validMove = false;
                while (!validMove) {
                    input1 = std::rand() % 3;  
                    input2 = std::rand() % 3;  
                    if (game.play(input1, input2)) {
                        validMove = true;
                        std::cout << "AI played (" << input1 << ", " << input2 << ")" << std::endl;
                    }
                }
            }
        }

        // Determine the outcome of the game
        if (game.hasWon(0)) {
            char winnerSymbol = 'X';
            std::string winnerName;
            std::cout << bold(red("Player X has won!")) << std::endl;
            std::cout << "Enter your name: ";
            std::cin >> winnerName;
            Stats winner(winnerName, game.turnCount, winnerSymbol);
            saveStats(winner);
        } else if (game.hasWon(1)) {
            std::cout << "Player O has won!" << std::endl;
        } else {
            std::cout << "It's a draw!" << std::endl;
        }

        std::cout << "Play again? (y = 0, n = 1)" << std::endl;
        std::cin >> gameInteger;
        std::system("clear");
       
    }
}

// ai_Results strongStrategy(int layerCount, int fieldSpace) {
//     int input1, input2;
//     bool validMove;
//     bool aboutToWin;
//     bool aboutToLose;
//     bool moveFound;
//     Vec returnStrat;
//     aboutToWin = false;
//     aboutToLose = false;
//     ai_Results foundPlay;
//     ai_Results setPlay;
//     foundPlay.set(-1,-1,10,-1);
//     setPlay.set(-1,-1,10,-1);
//                 while (!validMove) {
//                     moveFound = false;
//                     humanThreat = false;
//                     while (!moveFound) {
//                         game.currentTurn = 1;
//                         for (int i = 0; i < game.size; i++) {
//                             for (int j = 0; j < game.size; j++) {
//                                 if (game.pretend(i,j) == true) {
//                                     input1 = i;
//                                     input2 = j;
//                                     aboutToWin;
//                                 }

//                             }

//                         }

//                         if (!aboutToWin) {
//                             game.currentTurn = 0;
//                             for (int i = 0; i < game.size; i++) {
//                                 for (int j = 0; j < game.size; j++) {
//                                     if (game.pretend(i,j) == true) {
//                                         input1 = i;
//                                         input2 = j;
//                                         aboutToLose = true;
//                                     }

//                                 }

//                             }
                            
//                         }
//                     }
//                     if (aboutToWin == false && aboutToLose == false;){
//                         for int (i = 0, i < game.size; i++) {
//                             for int(j = 0, j < game.size(); j++){
//                                 if (shadowBoard[i][j] == -1) {
//                                     shadowBoard[i][j] = 1
//                                     for int(k = 0, k < game.size, k++) {
//                                         for int(l = 0, l < game.size, l++) {
//                                             if (shadowBoard[k][l] == -1){
//                                                 shadowBoard[k][l] = 0;
//                                             }
//                                         }
//                                     }
//                                 }
//                             }
//                         }
//                     }
//                     if (game.pretend(input1, input2)) {
//                         validMove = true;
//                         game
//                     }
//                 }
    
//     bool cycleBreak;
//     bool doubleBreak;
//     cycleBreak = false;
//     doubleBreak = false;
//     for (int i = 0; i < fieldSpace; i++) {
//         if (cycleBreak == true) {
//             break;
//         }
//         for (int j = 0; j < fieldSpace; j++){
//             if (game.shadowBoard[i][j] == -1) {
//                 game.shadowBoard[i][j] = 1;
//                 if (game.foresight(1) == true) {
//                     cycleBreak == true;
//                     foundPlay.set(i,j,(layerCount + 1),0);
//                     break;
//                 }
//                 doubleBreak = false;
//                 for (int k = 0; k < fieldSpace; k++) {
//                     if (doubleBreak == true) {
//                         break;
//                     }
//                     for (int l = 0; l < fieldSpace; l++) {
//                         if (game.shadowBoard[k][l] == -1){
//                             game.shadowBoard[k][l] = 0;
//                             currentTurn = 0;
//                             if (game.foresight(0) == true) {
//                                 doubleBreak = true;
//                                 foundPlay.set(k,l,( layerCount + 2),1);
//                                 break;
//                             }
//                             setPlay = strongStrategy((layerCount + 2), fieldSpace);
//                         }
//                     }
//                 }
//             }
//         }
//     }
//     return foundPlay;
                
// }

// void strong_AI (int tttInteger) {
//     int gameInteger = tttInteger;
//     while (gameInteger == 0) {
//         GameState game;
//         int input1, input2;
//         bool validMove;
//         bool humanThreat;
//         bool moveFound;
//         ai_Results optimalPlay;


//         while (!game.done) {
//             std::system("clear");
//             std::cout << game << std::endl;  

//             if (game.currentTurn == 0) {  // Player's turn
//                 validMove = false;
//                 while (!validMove) {
//                     std::cout << "Your turn. Enter row and column numbers (0-2): ";
//                     if (!(std::cin >> input1 >> input2)) {
//                         std::cin.clear();  
//                         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  
//                         std::cout << "Invalid input. Please enter numbers only." << std::endl;
//                         continue;  
//                     }
//                     std::cout << "Input received: " << input1 << ", " << input2 << std::endl; 
//                     if (game.play(input1, input2)) {
//                         validMove = true;
//                     } else {
//                         std::cout << "Invalid move. Please try again." << std::endl;
//                     }
//                 }
//             } else {  // AI's turn
//                 validMove = false;
//                 while (!validMove) {

//                     moveFound = false;
//                     humanThreat = false;
//                     while (!moveFound) {
//                         game.currentTurn = 0;
//                         for (int i = 0; i < game.size; i++) {
//                             for (int j = 0; j < game.size; j++) {
//                                 if (game.pretend(i,j) == true) {
//                                     input1 = i;
//                                     input2 = j;
//                                     humanThreat = true;
//                                     moveFound = true;
//                                 }

//                             }

//                         }

//                         if (!humanThreat) {
//                             game.currentTurn = 1;
//                             for (int i = 0; i < game.size; i++) {
//                                 for (int j = 0; j < game.size; j++) {
//                                     if (game.pretend(i,j) == true) {
//                                         input1 = i;
//                                         input2 = j;
//                                         moveFound = true;
//                                     }

//                                 }

//                             }
                            
//                         }
//                     }
//                     if (!moveFound){
//                         input1 = std::rand() % 3;  
//                         input2 = std::rand() % 3; 
//                     }
//                     if (game.play(input1, input2)) {
//                         validMove = true;
//                         std::cout << "AI played (" << input1 << ", " << input2 << ")" << std::endl;
//                     }
//                 }
//             }
//         }

//         // Determine the outcome of the game
//         if (game.hasWon(0)) {
//             char winnerSymbol = 'X';
//             std::string winnerName;
//             std::cout << bold(red("Player X has won!")) << std::endl;
//             std::cout << "Enter your name: ";
//             std::cin >> winnerName;
//             Stats winner(winnerName, game.turnCount, winnerSymbol);
//             saveStats(winner);
//         } else if (game.hasWon(1)) {
//             std::cout << "Player O has won!" << std::endl;
//         } else {
//             std::cout << "It's a draw!" << std::endl;
//         }

//         std::cout << "Play again? (y = 0, n = 1)" << std::endl;
//         std::cin >> gameInteger;
//         std::system("clear");
       
//     }
// }

void pve(){
    weak_AI(0);
}


#endif

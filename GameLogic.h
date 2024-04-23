#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H


#include <iostream>
#include "GameState.h"

void ticTacToe_Single (int tttInteger) {
    gameInteger = tttInteger;
    while (gameInteger == 1) {
        GameState game;
        int input1 = -1;
        int input2 = -1;

        while (game.done == false) {
            std::cin >> input1;
            std::cin >> input2;
            game.play(input1,input2);

        }
    }
}


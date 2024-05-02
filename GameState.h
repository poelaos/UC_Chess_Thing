#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <iostream>
#include <string>

#define RESET "\033[0m"
#define BOLD "\033[1m"
#define BLUE "\033[94m"
#define RED "\033[91m"
 
std::string bold(std::string letter) {
    std::string result = BOLD;
    result += letter;
    result += RESET;
    return result;
}


std::string blue(std::string letter) {
    std::string result = BLUE;
    result += letter;
    result += RESET;
    return result;
}

std::string red(std::string letter) {
    std::string result = RED;
    result += letter;
    result += RESET;
    return result;
}

bool withinBounds(int x, int y) {
    if ((x >= 0 && x <= 2) && (y >= 0 && y <= 2)) {
        return true;
    }
    return false;

}

struct Vec{
    int x;
    int y;

    Vec(){
        x = 0;
        y = 0;
    }

    Vec(int x, int y){
        this->x = x;
        this->y = y;
    }

    void set(int x, int y){
        this->x = x;
        this->y = y;
    }
};

std::ostream& operator<<(std::ostream& os, const Vec& v){
    os << "(" << v.x << ", " << v.y << ")";

    return os;
}

struct GameState;
std::ostream& operator<<(std::ostream& os, const GameState& state);

struct GameState{
    int** grid;
    bool currentTurn;
    int size;
    int turnCount;

    bool done;
    Vec lastMove;

    GameState(){
        size = 3;
        currentTurn = 0;
        turnCount = 0;
        done = false;

        lastMove.set(-1, -1);

        grid = new int*[size];

        for (int i = 0; i < size; i++){
            grid[i] = new int[size];
            for (int j = 0; j < size; j++){
                grid[i][j] = -1;
            }
        }
    }

    GameState(int size){
        this->size = size;
        currentTurn = 0;
        turnCount = 0;
        done = false;

        lastMove.set(-1, -1);

        grid = new int*[size];

        for (int i = 0; i < size; i++){
            grid[i] = new int[size];
            for (int j = 0; j < size; j++){
                grid[i][j] = -1;
            }
        }
    }

    GameState(const GameState& other){
        size = other.size;
        currentTurn = other.currentTurn;
        turnCount = other.turnCount;
        done = other.done;
        lastMove = other.lastMove;

        grid = new int*[size];

        for (int i = 0; i < size; i++){
            grid[i] = new int[size];
            for (int j = 0; j < size; j++){
                grid[i][j] = other.grid[i][j];
            }
        }
    }

    bool operator==(const GameState& other){
        bool sizeMatch = size == other.size;
        bool currentTurnMatch = currentTurn == other.currentTurn;
        bool turnCountMatch = turnCount == other.turnCount;
        bool doneMatch = done == other.done;
        bool lastMoveMatch = lastMove.x == other.lastMove.x && lastMove.y == other.lastMove.y;
        if (sizeMatch && currentTurnMatch && turnCountMatch && doneMatch && lastMoveMatch){
            for (int i = 0; i < size; i++){
                for (int j = 0; j < size; j++){
                    if (grid[i][j] != other.grid[i][j]){
                        return false;
                    }
                }
            }
            
            return true;
        }
        else{
            return false;
        }
    }

    GameState& operator=(const GameState& other){
        currentTurn = other.currentTurn;
        turnCount = other.turnCount;
        done = other.done;
        lastMove = other.lastMove;

        if (size == other.size){
            for (int i = 0; i < size; i++){
                for (int j = 0; j < size; j++){
                    grid[i][j] = other.grid[i][j];
                }
            }
        }
        else{
            
            for (int i = 0; i < size; i++){
                delete[] grid[i];
            }
            delete[] grid;

            size = other.size;

            grid = new int*[size];

            for (int i = 0; i < size; i++){
                grid[i] = new int[size];
                for (int j = 0; j < size; j++){
                    grid[i][j] = other.grid[i][j];
                }
            }
        }

        return *this;
    }

    bool hasWon(int player){
        for (int i = 0; i < size; i++){
            int count = 0;
            for (int j = 0; j < size; j++){
                if (grid[i][j] == player){
                    count++;
                }
            }
            if (count == size){
                return true;
            }
        }
        for (int i = 0; i < size; i++){
            int count = 0;
            for (int j = 0; j < size; j++){
                if (grid[j][i] == player){
                    count++;
                }
            }
            if (count == size){
                return true;
            }
        }
        int mainDiagCount = 0;
        for (int i = 0; i < size; i++){
            if (grid[i][i] == player){
                mainDiagCount++;
            }
        }
        if (mainDiagCount == size){
            return true;
        }

        int secondaryDiagCount = 0;
        for (int i = 0; i < size; i++){
            if (grid[i][size-1-i] == player){
                secondaryDiagCount++;
            }
        }
        if (secondaryDiagCount == size){
            return true;
        }
        

        return false;
    }

    bool play(int x, int y){
        if (grid[x][y] != -1){
            return false;
        }

        grid[x][y] = currentTurn;
        currentTurn = !currentTurn;
        turnCount++;
        lastMove.set(x, y);

        if (turnCount == size * size){
            done = true;
        }
        else if (hasWon(0) || hasWon(1)){
            done = true;
        }

        return true;
    }

    ~GameState(){
        for (int i = 0; i < size; i++){
            delete[] grid[i];
        }
        delete[] grid;
    }
};

std::ostream& operator<<(std::ostream& os, const GameState& state){
    os << "   ";
    for (int j = 0; j < state.size; j++){
        os << " " << j << "  ";
    }
    os << std::endl;
    os << "   ";
    for (int j = 0; j < state.size; j++){
        os << "--- ";
    }
    os << std::endl;
   for (int i = 0; i < state.size; i++){
        os << i << " ";
        for (int j = 0; j < state.size; j++){
            std::string c = " ";
            if (state.grid[i][j] == 0){
                c = 'X';
                c = bold(red(c));
            }
            else if (state.grid[i][j] == 1){
                c = 'O';
                c = bold(blue(c));
            }
            os << "| " << c << " ";
            if (j == state.size - 1) os << "|";
        }
        os << std::endl << "   ";
        for (int j = 0; j < state.size; j++){
            os << "--- ";
        }
        os << std::endl;
    }

    return os;
}

#endif



EXPERIMENTAL CHANGES BELOW, IF YOU DO NOT WANT THIS IN CODE, STOP YOUR COPY AND PASTE HERE:

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <iostream>
#include <string>

#define RESET "\033[0m"
#define BOLD "\033[1m"
#define BLUE "\033[94m"
#define RED "\033[91m"
 
std::string bold(std::string letter) {
    std::string result = BOLD;
    result += letter;
    result += RESET;
    return result;
}


std::string blue(std::string letter) {
    std::string result = BLUE;
    result += letter;
    result += RESET;
    return result;
}

std::string red(std::string letter) {
    std::string result = RED;
    result += letter;
    result += RESET;
    return result;
}


struct Vec{
    int x;
    int y;

    Vec(){
        x = 0;
        y = 0;
    }

    Vec(int x, int y){
        this->x = x;
        this->y = y;
    }

    void set(int x, int y){
        this->x = x;
        this->y = y;
    }
};

struct ai_Results{
    int x;
    int y;
    int numCount;
    int winLog;


    ai_Results(){
        x = 0;
        y = 0;
        numCount = 0;
        winLog = 0;
    }

    ai_Results(int x, int y){
        this->x = x;
        this->y = y;
        this->numCount = numCount;
        this->winLog = winLog;
    }

    void set(int x, int y, int numCount, int winLog){
        this->x = x;
        this->y = y;
        this->numCount = numCount;
        this->winLog = winLog;
    }
};


std::ostream& operator<<(std::ostream& os, const Vec& v){
    os << "(" << v.x << ", " << v.y << ")";

    return os;
}

struct GameState;
std::ostream& operator<<(std::ostream& os, const GameState& state);

struct GameState{
    int** grid;
    int** shadowBoard;
    bool currentTurn;
    int size;
    int turnCount;

    bool done;
    Vec lastMove;

    GameState(){
        size = 3;
        currentTurn = 0;
        turnCount = 0;
        done = false;

        lastMove.set(-1, -1);

        grid = new int*[size];
        shadowBoard = new int*[size];

        for (int i = 0;i < size; i++){
            grid[i] = new int[size];
            for (int j = 0; j < size; j++){
                grid[i][j] = -1;
            }
        }

        for (int i = 0; i < size; i++) {
            shadowBoard[i] = new int[size];
            for (int j = 0; j < size; j++){
                shadowBoard[i][j] = -1;
            }
        }

    }

    GameState(int size){
        this->size = size;
        currentTurn = 0;
        turnCount = 0;
        done = false;

        lastMove.set(-1, -1);

        grid = new int*[size];

        for (int i = 0; i < size; i++){
            grid[i] = new int[size];
            for (int j = 0; j < size; j++){
                grid[i][j] = -1;
            }
        }
        

        shadowBoard = new int*[size];

        for (int i = 0; i < size; i++){
            shadowBoard[i] = new int[size];
            for (int j = 0; j < size; j++) {
                shadowBoard[i][j] = -1;
            }
        }
    }

    GameState(const GameState& other){
        size = other.size;
        currentTurn = other.currentTurn;
        turnCount = other.turnCount;
        done = other.done;
        lastMove = other.lastMove;

        grid = new int*[size];

        for (int i = 0; i < size; i++){
            grid[i] = new int[size];
            for (int j = 0; j < size; j++){
                grid[i][j] = other.grid[i][j];
            }
        }
        shadowBoard = new int*[size];
        for (int i = 0; i < size; i++){
            shadowBoard[i] = new int[size];
            for (int j = 0; j < size; j++){
                grid[i][j] = other.grid[i][j];
            }
        }

    }

    bool operator==(const GameState& other){
        bool sizeMatch = size == other.size;
        bool currentTurnMatch = currentTurn == other.currentTurn;
        bool turnCountMatch = turnCount == other.turnCount;
        bool doneMatch = done == other.done;
        bool lastMoveMatch = lastMove.x == other.lastMove.x && lastMove.y == other.lastMove.y;
        if (sizeMatch && currentTurnMatch && turnCountMatch && doneMatch && lastMoveMatch){
            for (int i = 0; i < size; i++){
                for (int j = 0; j < size; j++){
                    if (grid[i][j] != other.grid[i][j]){
                        return false;
                    }
                }
            }
            
            return true;
        }
        else{
            return false;
        }
    }

    GameState& operator=(const GameState& other){
        currentTurn = other.currentTurn;
        turnCount = other.turnCount;
        done = other.done;
        lastMove = other.lastMove;

        if (size == other.size){
            for (int i = 0; i < size; i++){
                for (int j = 0; j < size; j++){
                    grid[i][j] = other.grid[i][j];
                }
            }
        }
        else{
            
            for (int i = 0; i < size; i++){
                delete[] grid[i];
            }
            delete[] grid;

            size = other.size;

            grid = new int*[size];

            for (int i = 0; i < size; i++){
                grid[i] = new int[size];
                for (int j = 0; j < size; j++){
                    grid[i][j] = other.grid[i][j];
                }
            }
        }

        return *this;
    }

    bool hasWon(int player){
        for (int i = 0; i < size; i++){
            int count = 0;
            for (int j = 0; j < size; j++){
                if (grid[i][j] == player){
                    count++;
                }
            }
            if (count == size){
                return true;
            }
        }
        for (int i = 0; i < size; i++){
            int count = 0;
            for (int j = 0; j < size; j++){
                if (grid[j][i] == player){
                    count++;
                }
            }
            if (count == size){
                return true;
            }
        }
        int mainDiagCount = 0;
        for (int i = 0; i < size; i++){
            if (grid[i][i] == player){
                mainDiagCount++;
            }
        }
        if (mainDiagCount == size){
            return true;
        }

        int secondaryDiagCount = 0;
        for (int i = 0; i < size; i++){
            if (grid[i][size-1-i] == player){
                secondaryDiagCount++;
            }
        }
        if (secondaryDiagCount == size){
            return true;
        }
        

        return false;
    }

    bool foresight(int player){
        for (int i = 0; i < size; i++){
            int count = 0;
            for (int j = 0; j < size; j++){
                if (shadowBoard[i][j] == player){
                    count++;
                }
            }
            if (count == size){
                return true;
            }
        }
        for (int i = 0; i < size; i++){
            int count = 0;
            for (int j = 0; j < size; j++){
                if (shadowBoard[j][i] == player){
                    count++;
                }
            }
            if (count == size){
                return true;
            }
        }
        int mainDiagCount = 0;
        for (int i = 0; i < size; i++){
            if (shadowBoard[i][i] == player){
                mainDiagCount++;
            }
        }
        if (mainDiagCount == size){
            return true;
        }

        int secondaryDiagCount = 0;
        for (int i = 0; i < size; i++){
            if (shadowBoard[i][size-1-i] == player){
                secondaryDiagCount++;
            }
        }
        if (secondaryDiagCount == size){
            return true;
        }
        

        return false;
    }

    bool play(int x, int y){
        if (!withinBounds(x, y)) {
            return false;
        }
        
        if (grid[x][y] != -1){
            return false;
        }

        grid[x][y] = currentTurn;
        currentTurn = !currentTurn;
        turnCount++;
        lastMove.set(x, y);

        if (turnCount == size * size){
            done = true;
        }
        else if (hasWon(0) || hasWon(1)){
            done = true;
        }

        return true;
    }

    bool pretend(int x, int y, int imaginaryTurn){
        if (shadowBoard[x][y] != -1){
            return false;
        }
        shadowBoard[x][y] = imaginaryTurn;
        if (foresight(imaginaryTurn) == false) {
            shadowBoard[x][y] = -1;
            return true;   
        }
        shadowBoard[x][y] = -1;
        return false;
    }
    

    void syncShadow() {
        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++) {
                shadowBoard[i][j] = grid[i][j];
            }
        } 
    }

ai_Results strongStrategy(int layerCount,) {
    int input1, input2;
    bool validMove;
    bool aboutToWin;
    bool aboutToLose;
    bool moveFound;
    Vec returnStrat;
    aboutToWin = false;
    aboutToLose = false;
    ai_Results foundPlay;
    ai_Results setPlay;
    lowestLayer = (10 - layerCount)
    foundPlay.set(-1,-1,layerCount,-1);
    setPlay.set(-1,-1,layerCount,-1);
    bool cycleBreak;
    bool doubleBreak;
    bool lossDanger;
    lossDanger = false;
    cycleBreak = false;
    doubleBreak = false;
    for (int i = 0; i < size; i++) {
        if (cycleBreak == true) {
            break;
        }
        for (int j = 0; j < size; j++){
            if (shadowBoard[i][j] == -1) {
                shadowBoard[i][j] = 1;
                if (foresight(1) == true) {
                    cycleBreak == true;
                    foundPlay.set(i,j,(layerCount + 1),0);
                    break;
                }
                doubleBreak = false;
                for (int k = 0; k < size; k++) {
                    if (doubleBreak == true) {
                        break;
                    }
                    for (int l = 0; l < size; l++) {
                        if (shadowBoard[k][l] == -1){
                            shadowBoard[k][l] = 0;
                            currentTurn = 0;
                            if (foresight(0) == true) {
                                doubleBreak = true;
                                foundPlay.set(k,l,(layerCount + 2),1);
                                break;
                            }
                            setPlay = strongStrategy((layerCount + 2));
                            if (setPlay.winLog == 0) {
                                lossDanger = true;
                                doubleBreak = true;
                                cycleBreak = true;
                                break;
                            }
                            if ((setPlay.numCount) <= (lowestLayer)) {
                                lowestLayer = setPlay // I stopped coding here;
                                
                            }
                        }
                    }
                }
            }
        }
    }

    if (setPlay.winLog == 0 && ) {
        foundPlay.set(setplay.x, setplay.y, setplay.numCount,)
    }
    )
    return foundPlay;
                
}
    ~GameState(){
        for (int i = 0; i < size; i++){
            delete[] grid[i];
        }
        delete[] grid;

        for (int i = 0; i < size; i++){
            delete[] shadowBoard[i];
        }
        delete[] shadowBoard;

    }
};

std::ostream& operator<<(std::ostream& os, const GameState& state){
    os << "   ";
    for (int j = 0; j < state.size; j++){
        os << " " << j << "  ";
    }
    os << std::endl;
    os << "   ";
    for (int j = 0; j < state.size; j++){
        os << "--- ";
    }
    os << std::endl;
   for (int i = 0; i < state.size; i++){
        os << i << " ";
        for (int j = 0; j < state.size; j++){
            std::string c = " ";
            if (state.grid[i][j] == 0){
                c = 'X';
                c = bold(red(c));
            }
            else if (state.grid[i][j] == 1){
                c = 'O';
                c = bold(blue(c));
            }
            os << "| " << c << " ";
            if (j == state.size - 1) os << "|";
        }
        os << std::endl << "   ";
        for (int j = 0; j < state.size; j++){
            os << "--- ";
        }
        os << std::endl;
    }

    return os;
}

#endif


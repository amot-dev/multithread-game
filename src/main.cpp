#include <iostream>
#include <string>
#include <thread>
#include "board.h"

int main(){
    std::pair position = std::make_pair(0,0);
    Board gameBoard(25);
    gameBoard.printBoard(position);
    return 0;
}
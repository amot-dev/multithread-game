#include <iostream>
#include <string>
#include <thread>
#include "board.h"

int main(){
    std::pair<int,int> position = std::make_pair(0,0);
    Board gameBoard(position);
    //gameBoard.printBoard();
    return 0;
}
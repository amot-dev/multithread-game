#include "board.h"
#include "interface.h"

int main(){
    std::pair position = std::make_pair(0,0);
    Interface interface;
    Board board(26);
    interface.printGame(board, position);
    return 0;
}
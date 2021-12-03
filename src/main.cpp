#include "board.h"
#include "global.h"
#include "interface.h"

int main(){
    std::pair position = std::make_pair(0,0);
    Interface interface;
    Board board(48);
    statusRows.enqueue("Character Name");
    statusRows.enqueue("==============");
    statusRows.enqueue("");
    statusRows.enqueue("HP: 25");
    interface.printGame(board, position);
    return 0;
}
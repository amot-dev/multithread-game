#include "interface.h"
#include <iostream>
#include "global.h"

Interface::Interface(){
    for (int i = 0; i < statusSpacingAmount; i++) statusSpacing.append(" ");
}

void Interface::setStatusSpacingAmount(int spacingAmount){
    statusSpacingAmount = spacingAmount;
    for (int i = 0; i < statusSpacingAmount; i++) statusSpacing.append(" ");
}

void Interface::printGame(const Board &board, std::pair<int,int> position) const{
    int viewSize = board.getViewSize();
    for (int i = 0; i < 100; i++) std::cout << std::endl;
    for (int i = (position.first - viewSize/2); i <= (position.first + viewSize/2); i++){
        for (int j = (position.second - viewSize/2); j <= (position.second + viewSize/2); j++){
            std::pair coordinates = std::make_pair(i,j);
            Tile tile = board.getTile(coordinates);

            if (coordinates == position) std::cout << "@  ";
            else std::cout << biomeChars.at(tile.getBiome()) << "  ";
        }
        std::cout << statusSpacing << statusRows.tryDequeue() << std::endl;
    }
}
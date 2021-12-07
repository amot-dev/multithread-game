#include "interface.h"

#include <iostream>
#include "exceptions.h"
#include "global.h"

Interface::Interface(){
    for (int i = 0; i < statusSpacingAmount; i++) statusSpacing.append(" ");
}

void Interface::setStatusSpacingAmount(int spacingAmount){
    statusSpacingAmount = spacingAmount;
    for (int i = 0; i < statusSpacingAmount; i++) statusSpacing.append(" ");
}

void Interface::printGame(const Board& board, std::pair<int,int> position, bool useNewlines) const{
    int viewSize = board.getViewSize();
    if (useNewlines) for (int i = 0; i < 100; i++) std::cout << std::endl;
    for (int i = (position.first - viewSize/2); i <= (position.first + viewSize/2); i++){
        for (int j = (position.second - viewSize/2); j <= (position.second + viewSize/2); j++){
            std::pair here = std::make_pair(i,j);
            Tile tile = board.getTile(here);

            if (here == position) std::cout << playerChar << "  ";
            else if (tile.getFeature() != featGen.none){
                try{std::cout << featureChars.at(tile.getFeature()) << "  ";}
                catch(const std::exception&){throw InvalidFeatureFound();};
            }
            else {
                try{std::cout << biomeChars.at(tile.getBiome()) << "  ";}
                catch(const std::exception&){throw InvalidBiomeFound();};
            }
        }
        std::cout << statusSpacing << statusRows.tryDequeue() << std::endl;
    }
}
#include "board.h"
#include <cmath>
#include "utility.h"
#include "exceptions.h"

Board::Board(){
    srand(time(0));
    generateBoard();
}

Board::Board(int seed){
    srand(seed);
    generateBoard();
}

Board::~Board(){}

int Board::getViewSize() const {
    return viewSize;
}

Tile Board::getTile(std::pair<int,int> coordinates) const {
    if (!tileExists(coordinates)) throw TileMissingException();
    return board.at(coordinates);
}

void Board::generateBoard(){
    for (int i = -viewSize/2; i <= viewSize/2; i++){
        for (int j = -viewSize/2; j <= viewSize/2; j++){
            std::pair coordinates = std::make_pair(i,j);
            generateTile(coordinates);
        }
    }
}

void Board::generateTile(std::pair<int,int> coordinates){
    generateBiome(coordinates);
}

void Board::generateBiome(std::pair<int,int> coordinates){
    if (tileExists(coordinates)) return;
    Tile tile;
    int biome = pickByProbability(tileGen.biomeChances);
    tile.biome = biome;
    std::pair biomeSize = std::make_pair(randInt(tileGen.minBiomeSize,tileGen.maxBiomeSize),randInt(tileGen.minBiomeSize,tileGen.maxBiomeSize));

    if (!tileExists(std::make_pair(coordinates.first+1,coordinates.second-1))) coordinates.first += biomeSize.first;
    else if (!tileExists(std::make_pair(coordinates.first,coordinates.second-1))) coordinates.second -= biomeSize.second;
    else if (!tileExists(std::make_pair(coordinates.first,coordinates.second+1))) coordinates.second += biomeSize.second;
    else if (!tileExists(std::make_pair(coordinates.first-1,coordinates.second))) coordinates.first -= biomeSize.first;
    else {
        tile.biome = board.at(std::make_pair(coordinates.first-1, coordinates.second)).biome;
        board.emplace(coordinates, tile);
    }
    
    int y = tileGen.minBiomeSize;
    for (int i = (coordinates.first - biomeSize.first); i <= (coordinates.first + biomeSize.first); i++){
        if (i == coordinates.first) y = biomeSize.second;
        else if (i < coordinates.first) y = randInt(y,biomeSize.second);
        else if (i > coordinates.first) y = randInt(tileGen.minBiomeSize,y);
        for (int j = (coordinates.second - y); j <= (coordinates.second + y); j++){
            std::pair here = std::make_pair(i,j);
            if (!tileExists(here)) board.emplace(here, tile);
        }
    }
}

bool Board::tileExists(std::pair<int,int> coordinates) const {
    if (board.find(coordinates) == board.end()) return false;
    else return true;
}
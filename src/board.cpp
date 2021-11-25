#include "board.h"
#include <iostream>
#include <cmath>
#include "exceptions.h"

Board::Board(std::pair<int,int> position){
    board.emplace(position, generateTile(position));
    std::cout << board.size();
}

Board::~Board(){}

Board::Tile Board::generateTile(std::pair<int,int> coordinates){
    Tile generated;
    generated.biome = tileGen.plains;
    return generated;
}

int Board::determineBiomeForNewTile(std::pair<int, int> coordinates){
    int existingNearbyTiles = 0;
    std::map<int,int> nearbyBiomes = {
        {tileGen.plains,0},
        {tileGen.forest,0},
        {tileGen.ocean,0},
        {tileGen.desert,0},
        {tileGen.mountains,0}
    };
    for (int i = coordinates.first - 1; i <= coordinates.first + 1; i++){
        for (int j = coordinates.second - 1; i <= coordinates.first + 1; j++){
            if (i != coordinates.first && j != coordinates.second){
                if (tileExists(std::make_pair(i,j))){
                    int biome = board.at(std::make_pair(i,j)).biome;
                    existingNearbyTiles++;
                    nearbyBiomes.at(biome)++;
                }
            }
        }
    }
    std::map<int,double> biomeWeights = {
        {tileGen.plains,getBiomeWeight(tileGen.plains, 5)},
        {tileGen.forest,0},
        {tileGen.ocean,0},
        {tileGen.desert,0},
        {tileGen.mountains,0}
    };
}

double Board::getBiomeWeight(int biome, int nearbyOccurences){
    std::cout << (1 - pow(1-tileGen.biomeChances.at(biome),nearbyOccurences+1));
    return (1 - pow(1-tileGen.biomeChances.at(biome),nearbyOccurences+1));
}

bool Board::tileExists(std::pair<int,int> coordinates){
    if (board.find(coordinates) == board.end()) return false;
    else return true;
}

void Board::printBoard(std::pair<int,int> position){
    //TODO
}
#include "board.h"
#include <iostream>
#include <cmath>
#include "utility.h"
#include "exceptions.h"

Board::Board(std::pair<int,int> position){
    board.emplace(position, generateTile(position));
    //TODO
}

Board::~Board(){}

Board::Tile Board::generateTile(std::pair<int,int> coordinates){
    Tile generated;
    generated.biome = determineBiomeForNewTile(coordinates);
    return generated;
}

int Board::determineBiomeForNewTile(std::pair<int, int> coordinates){
    std::map<int,int> nearbyBiomes = {
        {tileGen.plains,0},
        {tileGen.forest,0},
        {tileGen.ocean,0},
        {tileGen.desert,0},
        {tileGen.mountains,0}
    };
    for (int i = coordinates.first - 1; i <= coordinates.first + 1; i++){
        for (int j = coordinates.second - 1; j <= coordinates.second + 1; j++){
            if (i != coordinates.first && j != coordinates.second){
                if (tileExists(std::make_pair(i,j))){
                    int biome = board.at(std::make_pair(i,j)).biome;
                    nearbyBiomes.at(biome)++;
                }
            }
        }
    }
    nearbyBiomes.at(tileGen.ocean)++;
    std::map<int,double> biomeWeights = {
        {tileGen.plains,getBiomeWeight(tileGen.plains, nearbyBiomes.at(tileGen.plains))},
        {tileGen.forest,getBiomeWeight(tileGen.forest, nearbyBiomes.at(tileGen.forest))},
        {tileGen.ocean,getBiomeWeight(tileGen.ocean, nearbyBiomes.at(tileGen.ocean))},
        {tileGen.desert,getBiomeWeight(tileGen.desert, nearbyBiomes.at(tileGen.desert))},
        {tileGen.mountains,getBiomeWeight(tileGen.mountains, nearbyBiomes.at(tileGen.mountains))}
    };
    return pickByProbability(biomeWeights);
}

double Board::getBiomeWeight(int biome, int nearbyOccurences){
    return (1 - pow(1-tileGen.biomeChances.at(biome),nearbyOccurences+1));
}

bool Board::tileExists(std::pair<int,int> coordinates){
    if (board.find(coordinates) == board.end()) return false;
    else return true;
}

void Board::printBoard(std::pair<int,int> position){
    //TODO
}
#include <algorithm>
#include <cmath>
#include <random>
#include <vector>

#include "tile.h"
#include "utility.h"

#include "global.h"

Tile::Tile(){}

Tile::Tile(Board* board, std::pair<int,int> coordinates) : board(board), coordinates(coordinates){
    generateBiome();
    generateFeature();
}

Tile::Tile(Board* board, int biome) : board(board), biome(biome){
    ready = false;
    feature = featGen.none;
    travelCost = tileGen.biomeTravelCosts.at(biome);
};

int Tile::getBiome() const {return biome;}

void Tile::setFeature(int newFeature) {feature = newFeature;}

int Tile::getFeature() const {return feature;}

int Tile::getTravelCost() const {return travelCost;}

bool Tile::isTravellable() const {
    if (tileGen.biomeTravelCosts.at(biome) == 1000) return false;
    else return true;
}

bool Tile::isReady() const {return ready;}

void Tile::generateBiome(){
    biome = pickByProbability(tileGen.biomeChances);
    travelCost = tileGen.biomeTravelCosts.at(biome);

    std::pair<int,int> biomeSize = std::make_pair(randInt(tileGen.minBiomeSize,tileGen.maxBiomeSize),randInt(tileGen.minBiomeSize,tileGen.maxBiomeSize));
    if (!board->tileExists(std::make_pair(coordinates.first+1,coordinates.second-1))) coordinates.first += biomeSize.first;
    else if (!board->tileExists(std::make_pair(coordinates.first,coordinates.second-1))) coordinates.second -= biomeSize.second;
    else if (!board->tileExists(std::make_pair(coordinates.first,coordinates.second+1))) coordinates.second += biomeSize.second;
    else if (!board->tileExists(std::make_pair(coordinates.first-1,coordinates.second))) coordinates.first -= biomeSize.first;
    else {
        Tile adjacentTile = Tile(board, board->getTile(std::make_pair(coordinates.first-1, coordinates.second)).getBiome());
        board->setTile(coordinates, adjacentTile);
    }
    
    int y = tileGen.minBiomeSize;
    for (int i = (coordinates.first - biomeSize.first); i <= (coordinates.first + biomeSize.first); i++){
        if (i == coordinates.first) y = biomeSize.second;
        else if (i < coordinates.first) y = randInt(y,biomeSize.second);
        else if (i > coordinates.first) y = randInt(tileGen.minBiomeSize,y);
        for (int j = (coordinates.second - y); j <= (coordinates.second + y); j++){
            std::pair<int,int> here = std::make_pair(i,j);
            Tile tile = Tile(board, biome);
            if (!board->tileExists(here)) board->setTile(here, tile);
        }
    }
}

void Tile::generateFeature(){
    if (isTravellable()) return; //TEMPORARY (no features on ocean or mountains yet)

    int feature = 0;
    if (pickValue(featGen.featureChance)) feature = pickByProbability(featGen.featureChances);
    if (feature != featGen.city) return;

    int numDistricts = randInt(featGen.minCityDistricts, featGen.maxCityDistricts);
    if (numDistricts > 1){
        int cityRadius = (int)floor(ceil(sqrt(numDistricts))/2);

        bool generateHarbour = false;
        if (numDistricts > 2){
            generateHarbour = true;
            numDistricts--;
        }
        std::queue<int> districtsToGenerate;
        for (int i = 0; i < numDistricts; i++){
            if (i == 0) districtsToGenerate.push(featGen.cityMarket);
            else districtsToGenerate.push(pickByProbability(featGen.cityDistrictChances));
        }
        
        std::vector<std::pair<int,int>> coordinatesInRadius = getCoordinatesInRadius(coordinates, cityRadius);
        std::shuffle(coordinatesInRadius.begin(), coordinatesInRadius.end(), std::default_random_engine(board->getSeed()));

        for (auto& here : coordinatesInRadius){
            if (!board->tileExists(here)) {
                Tile tile = Tile(board, here);
                board->setTile(here, tile);
            }
            if (board->getTile(here).isTravellable() && board->getTile(here).getFeature() == featGen.none){
                if (generateHarbour){
                    std::vector<std::pair<int,int>> adjacentCoordinates = getAdjacentCoordinates(here);
                    for (auto& adjacent : adjacentCoordinates){
                        if (board->tileExists(adjacent) && board->getTile(adjacent).getBiome() == tileGen.ocean){
                            board->getTile(here).setFeature(featGen.cityHarbour);
                            generateHarbour = false;
                            break;
                        }
                    }
                }
                if (board->getTile(here).getFeature() == featGen.none){
                    if (!districtsToGenerate.empty()){
                        board->getTile(here).setFeature(districtsToGenerate.front());
                        districtsToGenerate.pop();
                    }
                }
            }
        }
    }
}
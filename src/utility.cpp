#include "utility.h"

#include <ctime>
#include <fstream>
#include <cereal/archives/json.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/utility.hpp>
#include "exceptions.h"

int randInt(int min, int max){
    return rand() % max + min;
}

bool pickValue(double probability){
    double random = ((double)rand()/RAND_MAX);
    return probability >= random;
}

int pickByProbability(std::map<int, double> map){
    double totalVal = 0;
    for (auto const& [key, val] : map) {
        totalVal += val;
    }

    double random = ((double)rand()/RAND_MAX) * totalVal;
    
    double incrementalProbability = 0;
    for (auto const& [key, val] : map){
        incrementalProbability += val;
        if (incrementalProbability >= random) return key;
    }
    return -1;
}

std::vector<std::pair<int,int>> getCoordinatesInRadius(std::pair<int,int> coordinates, int radius) {
    std::vector<std::pair<int,int>> coordinatesInRadius;
    coordinatesInRadius.reserve(radius*radius);
    for (int i = coordinates.first - radius; i <= coordinates.first + radius; i++){
        for (int j = coordinates.second - radius; j <= coordinates.second + radius; j++){
            coordinatesInRadius.push_back(std::make_pair(i,j));
        }
    }
    return coordinatesInRadius;
}

std::vector<std::pair<int,int>> getCoordinatesInRing(std::pair<int,int> coordinates, int radius) {
    std::vector<std::pair<int,int>> coordinatesInRing;
    coordinatesInRing.reserve(8*radius);
    for (int i = coordinates.first - radius; i <= coordinates.first + radius; i++){
        if (i == coordinates.first - radius || i == coordinates.first + radius){
            for (int j = coordinates.second - radius; j <= coordinates.second + radius; j++){
                coordinatesInRing.push_back(std::make_pair(i,j));
            }
        }
        else {
            coordinatesInRing.push_back(std::make_pair(i, coordinates.second - radius));
            coordinatesInRing.push_back(std::make_pair(i, coordinates.second + radius));
        }
    }
    return coordinatesInRing;
}

std::vector<std::pair<int,int>> getAdjacentCoordinates(std::pair<int,int> coordinates) {
    std::vector<std::pair<int,int>> adjacentCoordinates;
    adjacentCoordinates.reserve(4);
    adjacentCoordinates.push_back(std::make_pair(coordinates.first-1,coordinates.second));
    adjacentCoordinates.push_back(std::make_pair(coordinates.first,coordinates.second-1));
    adjacentCoordinates.push_back(std::make_pair(coordinates.first,coordinates.second+1));
    adjacentCoordinates.push_back(std::make_pair(coordinates.first+1,coordinates.second));
    return adjacentCoordinates;
}

void save(Board board, std::string savename){
    savename.append(".json");
    std::ofstream ofile(savename);
    {
        cereal::JSONOutputArchive oarchive(ofile);
        oarchive(board);
    }
}

Board load(std::string savename, std::pair<int,int> position){
    Board board;
    savename.append(".json");
    std::ifstream ifile(savename);
    {
        cereal::JSONInputArchive iarchive(ifile);
        iarchive(board);
    }
    if (!board.verify(position)) throw InvalidBoardLoad();
    return board;
}
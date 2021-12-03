#include "board.h"
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include "utility.h"
#include "exceptions.h"
#include "global.h"

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
    int biome = pickByProbability(tileGen.biomeChances);
    Tile tile = Tile(biome);
    std::pair biomeSize = std::make_pair(randInt(tileGen.minBiomeSize,tileGen.maxBiomeSize),randInt(tileGen.minBiomeSize,tileGen.maxBiomeSize));

    if (!tileExists(std::make_pair(coordinates.first+1,coordinates.second-1))) coordinates.first += biomeSize.first;
    else if (!tileExists(std::make_pair(coordinates.first,coordinates.second-1))) coordinates.second -= biomeSize.second;
    else if (!tileExists(std::make_pair(coordinates.first,coordinates.second+1))) coordinates.second += biomeSize.second;
    else if (!tileExists(std::make_pair(coordinates.first-1,coordinates.second))) coordinates.first -= biomeSize.first;
    else {
        Tile adjacentTile = Tile(board.at(std::make_pair(coordinates.first-1, coordinates.second)).getBiome());
        board.emplace(coordinates, adjacentTile);
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

void Board::generateFeature(std::pair<int,int> coordinates){
    int feature = 0;
    if (pickValue(featGen.featureChance)) feature = pickByProbability(featGen.featureChances);

    if (feature == featGen.city){
        int districts = randInt(featGen.minCityDistricts, featGen.maxCityDistricts);
        if (districts > 1){
            std::vector coordinatesInRadius = getCoordinatesInRadius(coordinates, 1);
            for (auto& here : coordinatesInRadius){
                if (!tileExists(here)) generateBiome(here); //potentially dangerous line!!! could cause infinite world gen
                if (getTile(here).getBiome() == tileGen.ocean){
                    //TODO: search for nearby oceans
                }
            }
        }
    }
}

bool Board::tileExists(std::pair<int,int> coordinates) const {
    if (board.find(coordinates) == board.end()) return false;
    else return true;
}

bool Board::tileReady(std::pair<int,int> coordinates) const {
    if (!tileExists(coordinates)) return false;
    return board.at(coordinates).isReady();
}

std::vector<std::pair<int,int>> Board::getCoordinatesInRadius(std::pair<int,int> coordinates, int radius) const {
    std::vector<std::pair<int,int>> coordinatesInRadius;
    coordinatesInRadius.reserve(radius*radius);
    for (int i = coordinates.first - radius; i <= coordinates.first + radius; i++){
        for (int j = coordinates.second - radius; j <= coordinates.second + radius; j++){
            coordinatesInRadius.push_back(std::make_pair(i,j));
        }
    }
    return coordinatesInRadius;
}

std::vector<std::pair<int,int>> Board::getAdjacentCoordinates(std::pair<int,int> coordinates) const {
    std::vector<std::pair<int,int>> adjacentCoordinates;
    adjacentCoordinates.reserve(4);
    adjacentCoordinates.push_back(std::make_pair(coordinates.first-1,coordinates.second));
    adjacentCoordinates.push_back(std::make_pair(coordinates.first,coordinates.second-1));
    adjacentCoordinates.push_back(std::make_pair(coordinates.first,coordinates.second+1));
    adjacentCoordinates.push_back(std::make_pair(coordinates.first+1,coordinates.second));
    return adjacentCoordinates;
}

Path Board::pathTo(std::pair<int,int> start, int biome, int feature, bool ignoreTravelCost, int maxDistance, int toSkip, std::pair<int,int> end) const {
    bool checkBiome = false;
    bool checkFeature = false;
    if (biome != -1) checkBiome = true;
    if (feature != -1) checkFeature = true;
    
    std::queue<std::pair<int,int>> queue;
    std::priority_queue<std::pair<std::pair<int,int>, Path>,std::vector<std::pair<std::pair<int,int>, Path>>,CompareTravelCost> priorityQueue;

    std::unordered_set<std::pair<int,int>, pair_hash> visited;
    std::unordered_map<std::pair<int,int>, Path, pair_hash> map;

    if (ignoreTravelCost) queue.push(start);
    else priorityQueue.push(std::make_pair(start,Path()));

    visited.insert(start);
    map.emplace(start, Path());

    int distanceTravelled = 0;
    int matches = 0;
    while(!queue.empty() && distanceTravelled <= maxDistance){
        std::pair<int,int> previous;
        if (ignoreTravelCost){
            previous = queue.front();
            queue.pop();
        } 
        else {
            previous = priorityQueue.top().first;
            priorityQueue.pop();
        }

        for (auto& here : getAdjacentCoordinates(previous)){
            if (!visited.count(here)){
                visited.insert(here);

                Path path;
                path.tilesTraversed = map.at(previous).tilesTraversed + 1;
                path.travelCost = map.at(previous).travelCost + getTile(here).getTravelCost();
                path.steps.push_back(here);

                if (tileExists(here) && getTile(here).isTravellable()) {
                    if (ignoreTravelCost) queue.push(here);
                    else priorityQueue.push(std::make_pair(here, path));
                }
                
                map.emplace(here, path);
            }
            
            if (!checkBiome && !checkFeature){
                if (here == end) return map.at(here);
            }
            else{
                bool match = false;
                if (checkBiome && getTile(here).getBiome() == biome) match = true;
                if (checkFeature) match = false;
                if (checkFeature && getTile(here).getFeature() == feature) match = true;

                if (match) matches++;
                if (matches > toSkip) return map.at(here);
            }
        }
        map.erase(previous);
        distanceTravelled++;
    }
    Path path;
    path.tilesTraversed = -1;
    path.travelCost = -1;
    return path;
}

bool Board::CompareTravelCost::operator()(const std::pair<std::pair<int,int>,Path>& lhs, const std::pair<std::pair<int,int>,Path>& rhs) const {
    return lhs.second.travelCost < rhs.second.travelCost;
}
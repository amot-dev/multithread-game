#include "board.h"

#include <algorithm>
#include <queue>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include "exceptions.h"
#include "global.h"
#include "utility.h"

Board::Board(){
    seed = time(0);
    srand(seed);
    generateBoard();
}

Board::Board(int seed) : seed(seed){
    srand(seed);
    generateBoard();
}

Board::Board(int seed, std::map<std::pair<int,int>,Tile> loadBoard, std::pair<int,int> position) : seed(seed){
    board = loadBoard;
    auto viewableBoard = getCoordinatesInRadius(position, viewSize/2);
    for (auto& here : viewableBoard) if (!tileExists(here)) throw InvalidBoardLoad();
}

Board::~Board(){}

int Board::getViewSize() const {
    return viewSize;
}

Tile Board::getTile(std::pair<int,int> coordinates) const {
    if (!tileExists(coordinates)) throw TileMissingException();
    return board.at(coordinates);
}

Path Board::pathTo(std::pair<int,int> start, int biome, int feature, bool ignoreTravelCost, int maxDistance, int toSkip, std::pair<int,int> end) const {
    bool checkBiome = false;
    bool checkFeature = false;
    if (biome != -1) checkBiome = true;
    if (feature != -1) checkFeature = true;
    
    std::queue<std::pair<int,int>> queue;
    std::priority_queue<std::pair<std::pair<int,int>, Path>,std::vector<std::pair<std::pair<int,int>, Path>>,CompareTravelCost> priorityQueue;

    std::unordered_set<std::pair<int,int>, PairHash> visited;
    std::unordered_map<std::pair<int,int>, Path, PairHash> map;

    if (ignoreTravelCost) queue.push(start);
    else priorityQueue.push(std::make_pair(start,Path()));

    visited.insert(start);
    map.emplace(start, Path());

    int matches = 0;
    while(!queue.empty()){
        std::pair<int,int> previous;
        if (ignoreTravelCost){
            previous = queue.front();
            queue.pop();
        } 
        else {
            previous = priorityQueue.top().first;
            priorityQueue.pop();
        }

        if (!tileExists(previous)) continue;

        for (auto& here : getAdjacentCoordinates(previous)){
            if (!visited.count(here)){
                visited.insert(here);

                if (!tileExists(here)) continue;

                Path path;
                path.tilesTraversed = map.at(previous).tilesTraversed + 1;
                path.travelCost = map.at(previous).travelCost + getTile(here).getTravelCost();
                path.steps.push_back(here);

                if (path.tilesTraversed > maxDistance) break;

                if (ignoreTravelCost) queue.push(here);
                else if (getTile(here).isTravellable()) priorityQueue.push(std::make_pair(here, path));
                
                map.emplace(here, path);

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
        }
        map.erase(previous);
    }
    Path path;
    path.tilesTraversed = -1;
    path.travelCost = -1;
    return path;
}

void Board::generateBoard(){
    for (int radius = 0; radius <= viewSize/2; radius++){
        auto coordinatesInRing = getCoordinatesInRing(std::make_pair(0,0), radius);
        for (auto& here : coordinatesInRing){
            generateTile(here);
        }
    }
}

void Board::generateTile(std::pair<int,int> coordinates){
    generateBiome(coordinates);
    generateFeature(coordinates);
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
    if (!getTile(coordinates).isTravellable()) return; //TEMPORARY (no features on ocean or mountains yet)
    int feature = 0;
    if (pickValue(featGen.featureChance)) feature = pickByProbability(featGen.featureChances);
    board.at(coordinates).setFeature(feature);
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
        
        std::vector coordinatesInRadius = getCoordinatesInRadius(coordinates, cityRadius);
        std::shuffle(coordinatesInRadius.begin(), coordinatesInRadius.end(), std::default_random_engine(seed));

        for (auto& here : coordinatesInRadius){
            if (!tileExists(here)) generateBiome(here);
            if (getTile(here).isTravellable() && getTile(here).getFeature() == featGen.none){
                if (generateHarbour){
                    std::vector adjacentCoordinates = getAdjacentCoordinates(here);
                    for (auto& adjacent : adjacentCoordinates){
                        if (tileExists(adjacent) && getTile(adjacent).getBiome() == tileGen.ocean){
                            board.at(here).setFeature(featGen.cityHarbour);
                            generateHarbour = false;
                            break;
                        }
                    }
                }
                if (getTile(here).getFeature() == featGen.none){
                    if (!districtsToGenerate.empty()){
                        board.at(here).setFeature(districtsToGenerate.front());
                        districtsToGenerate.pop();
                    }
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

std::vector<std::pair<int,int>> Board::getCoordinatesInRing(std::pair<int,int> coordinates, int radius) const {
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

std::vector<std::pair<int,int>> Board::getAdjacentCoordinates(std::pair<int,int> coordinates) const {
    std::vector<std::pair<int,int>> adjacentCoordinates;
    adjacentCoordinates.reserve(4);
    adjacentCoordinates.push_back(std::make_pair(coordinates.first-1,coordinates.second));
    adjacentCoordinates.push_back(std::make_pair(coordinates.first,coordinates.second-1));
    adjacentCoordinates.push_back(std::make_pair(coordinates.first,coordinates.second+1));
    adjacentCoordinates.push_back(std::make_pair(coordinates.first+1,coordinates.second));
    return adjacentCoordinates;
}

bool Board::CompareTravelCost::operator()(const std::pair<std::pair<int,int>,Path>& lhs, const std::pair<std::pair<int,int>,Path>& rhs) const {
    return lhs.second.travelCost < rhs.second.travelCost;
}
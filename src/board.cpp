#include "board.h"

#include <queue>
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

Board::~Board(){}

int Board::getViewSize() const {return viewSize;}

int Board::getSeed() const {return seed;}

Tile Board::getTile(std::pair<int,int> coordinates) const {
    if (!tileExists(coordinates)) throw TileMissingException();
    return world.at(coordinates);
}

bool Board::setTile(std::pair<int,int> coordinates, Tile tile){
    if (!tileExists(coordinates)){
        return world.emplace(coordinates, tile).second;
    }
    else {
        world.at(coordinates) = tile;
        return true;
    }
}

bool Board::verify(std::pair<int,int> position) const {
    auto viewableBoard = getCoordinatesInRadius(position, viewSize/2);
    for (auto& here : viewableBoard) if (!tileExists(here)) return false;
    return true;
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
                    int biomeHere = getTile(here).getBiome();
                    int featureHere = getTile(here).getFeature();

                    if (checkBiome && biomeHere == biome) match = true;
                    if (checkFeature) match = false;
                    if (checkFeature && (featureHere == feature || (feature == featGen.any && featureHere != featGen.none))) match = true;

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
            Tile tile = Tile(this, here);
            world.emplace(here, tile);
        }
    }
}

bool Board::tileExists(std::pair<int,int> coordinates) const {
    if (world.find(coordinates) == world.end()) return false;
    else return true;
}

bool Board::CompareTravelCost::operator()(const std::pair<std::pair<int,int>,Path>& lhs, const std::pair<std::pair<int,int>,Path>& rhs) const {
    return lhs.second.travelCost < rhs.second.travelCost;
}
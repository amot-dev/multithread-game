#ifndef UTILITY
#define UTILITY

#include <map>
#include <vector>
#include "board.h"

/**
 * @brief Implements hashing for pairs
 * 
 */
struct PairHash{
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2> &pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

/**
 * @brief Generates a random integer between min and max
 * 
 * @param min Smallest possible return value
 * @param max Largest possible return value
 * @return Randomly chosen int
 */
int randInt(int min, int max);

/**
 * @brief Picks a value (or doesn't) based on probability
 * 
 * @param probability The probability to pick a value
 * @return Whether or not the value was picked
 */
bool pickValue(double probability);

/**
 * @brief Pick a key from the map based on a probability value
 * 
 * @param map Map to pick from
 * @return Key returned 
 */
int pickByProbability(std::map<int, double> map);

/**
 * @brief Generates a vector of coordinates in a radius around some coordinates
 * 
 * @param coordinates x,y pair of coordinates
 * @param radius Radius to look around
 * @return A vector containing the requested coordinates 
 */
std::vector<std::pair<int,int>> getCoordinatesInRadius(std::pair<int,int> coordinates, int radius);
/**
 * @brief Generates a vector of coordinates in a ring at a radius around some coordinates
 * 
 * @param coordinates x,y pair of coordinates
 * @param radius Radius of ring to look at
 * @return A vector containing the requested coordinates
 */
std::vector<std::pair<int,int>> getCoordinatesInRing(std::pair<int,int> coordinates, int radius);
/**
 * @brief Generates a vector of coordinates adjacent some coordinates
 * 
 * Here, diagonal connections are not considered adjacent since 
 * diagonal moves are not allowed
 * 
 * @param coordinates A vector containing the requested coordinates
 * @return A vector containing the requested coordinates
 */
std::vector<std::pair<int,int>> getAdjacentCoordinates(std::pair<int,int> coordinates);

/**
 * @brief Saves the board to a file
 * 
 * @param board Board to save
 * @param savename Name to save under
 * @Whether or not to use json
 */
void save(Board board, std::string savename, bool json = false);

/**
 * @brief Loads board from a file
 * 
 * @param savename Name of save to load
 * @param position Position of the player
 * @param json Whether or not to use json
 */
Board load(std::string savename, std::pair<int,int> position, bool json = false);

#endif
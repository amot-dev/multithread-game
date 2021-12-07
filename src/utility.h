#ifndef UTILITY
#define UTILITY

#include <map>
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
 * @brief Saves the board to a file
 * 
 * @param savename Name to save under
 */
void save(Board board, std::string savename);

/**
 * @brief Loads board from a file
 * 
 * @param savename Name of save to load
 */
Board load(std::string savename);

#endif
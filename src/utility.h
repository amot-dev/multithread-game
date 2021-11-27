#ifndef UTILITY
#define UTILITY

#include <map>

/** Pick a key from the map based on a probability value
*
* @param map Map to pick from
* @return Key returned
*/
int pickByProbability(std::map<int, double> map);

#endif
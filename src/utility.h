#ifndef UTILITY
#define UTILITY

#include<map>

template<typename T1, typename T2>
/** Flip first and second values of a pair
    *
    * @param p Pair to flip
    * @return Flipped pair
*/
std::pair<T2,T1> flipPair(std::pair<T1,T2> p);

template<typename T1, typename T2>
/** Flip keys and values of map into multimap
    *
    * @param p Map to flip
    * @return Flipped multimap
*/
std::multimap<T2,T1> flipMap(std::map<T1,T2> mapIn);

#endif
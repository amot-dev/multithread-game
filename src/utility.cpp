#include "utility.h"
#include <algorithm>

template<typename T1, typename T2>
std::pair<T2,T1> flipPair(std::pair<T1,T2> p){return std::pair<T2,T1>(p.second, p.first);}

template<typename T1, typename T2>
std::multimap<T2,T1> flipMap(std::map<T1,T2> mapIn){
    std::multimap<T2,T1> mapOut;
    std::transform(mapIn.begin(), mapIn.end(), std::inserter(mapOut, mapOut.begin()), 
                   flipPair<T1,T2>);
    return mapOut;
}
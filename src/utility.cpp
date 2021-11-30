#include "utility.h"
#include <ctime>

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
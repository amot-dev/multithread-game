#include "utility.h"

#include <ctime>
#include <fstream>
#include <cereal/archives/json.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/utility.hpp>

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

void save(Board board, std::string savename){
    savename.append(".json");
    std::ofstream ofile(savename);
    {
        cereal::JSONOutputArchive oarchive(ofile);
        oarchive(board);
    }
}

Board load(std::string savename){
    Board board;
    savename.append(".json");
    std::ifstream ifile(savename);
    {
        cereal::JSONInputArchive iarchive(ifile);
        iarchive(board);
    }
    return board;
}
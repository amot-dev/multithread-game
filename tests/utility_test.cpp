#include <gtest/gtest.h>
#include <cstdio>
#include "../src/board.h"
#include "../src/utility.h"

TEST(SaveLoad, SaveLoadRegular){
    auto position = std::make_pair(0,0);
    std::string filename = "saveloadregular";
    Board toSave;
    save(toSave, filename);
    Board toLoad = load(filename, position);
    
    EXPECT_EQ(toLoad.getSeed(), toSave.getSeed());

    auto coordinatesToCheck = getCoordinatesInRadius(position,toLoad.getViewSize()/2);
    for (auto& here : coordinatesToCheck){
        EXPECT_EQ(toLoad.getTile(here).isReady(), toSave.getTile(here).isReady());
        EXPECT_EQ(toLoad.getTile(here).getBiome(), toSave.getTile(here).getBiome());
        EXPECT_EQ(toLoad.getTile(here).getFeature(), toSave.getTile(here).getFeature());
    }

    filename.append(".json");
    std::remove(filename.c_str());
}
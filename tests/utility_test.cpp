#include <gtest/gtest.h>
#include <cstdio>
#include "../src/board.h"
#include "../src/utility.h"

TEST(SaveLoad, SaveLoadJSON){
    auto position = std::make_pair(0,0);
    std::string filename = "saveload";
    Board toSave;
    save(toSave, filename, true);
    Board toLoad = load(filename, position, true);
    
    EXPECT_EQ(toLoad.getSeed(), toSave.getSeed());

    auto coordinatesToCheck = getCoordinatesInRadius(position,toLoad.getViewSize()/2);
    for (auto& here : coordinatesToCheck){
        EXPECT_EQ(toLoad.getTile(here).isReady(), toSave.getTile(here).isReady());
        EXPECT_EQ(toLoad.getTile(here).getBiome(), toSave.getTile(here).getBiome());
        EXPECT_EQ(toLoad.getTile(here).getFeature(), toSave.getTile(here).getFeature());
    }

    filename.append(".save.json");
    std::remove(filename.c_str());
}

TEST(SaveLoad, SaveLoadBIN){
    auto position = std::make_pair(0,0);
    std::string filename = "saveload";
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

    filename.append(".save");
    std::remove(filename.c_str());
}
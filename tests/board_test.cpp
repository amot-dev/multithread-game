#include <gtest/gtest.h>
#include "../src/board.h"
#include "../src/utility.h"

TEST(PathTo, PathToCoordinatesNoCost){
    auto start = std::make_pair(0,0);
    auto end = std::make_pair(3,5);
    int biome = -1;
    int feature = -1;
    bool ignoreTravelCost = true;
    int maxDistance = 25;
    int toSkip = 0;

    int expectedTilesTraversed = 8;
    auto expectedDestination = std::make_pair(3,5);

    Board board = load("pathTo", start);
    auto calculatedPath = board.pathTo(start, biome, feature, ignoreTravelCost, maxDistance, toSkip, end);

    EXPECT_EQ(calculatedPath.tilesTraversed, expectedTilesTraversed);
    EXPECT_EQ(calculatedPath.steps.back().first, expectedDestination.first);
    EXPECT_EQ(calculatedPath.steps.back().second, expectedDestination.second);
}

TEST(PathTo, PathToCoordinatesNoCostBrokenDistance){
    auto start = std::make_pair(0,0);
    auto end = std::make_pair(3,5);
    int biome = -1;
    int feature = -1;
    bool ignoreTravelCost = true;
    int maxDistance = 1;
    int toSkip = 0;

    int expectedTilesTraversed = -1;

    Board board = load("pathTo", start);
    auto calculatedPath = board.pathTo(start, biome, feature, ignoreTravelCost, maxDistance, toSkip, end);

    EXPECT_EQ(calculatedPath.tilesTraversed, expectedTilesTraversed);
}

TEST(PathTo, PathToCoordinatesNoCostUselessSkip){
    auto start = std::make_pair(0,0);
    auto end = std::make_pair(3,5);
    int biome = -1;
    int feature = -1;
    bool ignoreTravelCost = true;
    int maxDistance = 25;
    int toSkip = 9;

    int expectedTilesTraversed = 8;
    auto expectedDestination = std::make_pair(3,5);

    Board board = load("pathTo", start);
    auto calculatedPath = board.pathTo(start, biome, feature, ignoreTravelCost, maxDistance, toSkip, end);

    EXPECT_EQ(calculatedPath.tilesTraversed, expectedTilesTraversed);
    EXPECT_EQ(calculatedPath.steps.back().first, expectedDestination.first);
    EXPECT_EQ(calculatedPath.steps.back().second, expectedDestination.second);
}

TEST(PathTo, PathToBiomeNoCostClose){
    TileGen tileGen;
    auto start = std::make_pair(0,0);
    int biome = tileGen.plains;
    int feature = -1;
    bool ignoreTravelCost = true;
    int maxDistance = 25;
    int toSkip = 0;

    int expectedTilesTraversed = 1;

    Board board = load("pathTo", start);
    auto calculatedPath = board.pathTo(start, biome, feature, ignoreTravelCost, maxDistance, toSkip);

    EXPECT_EQ(calculatedPath.tilesTraversed, expectedTilesTraversed);
    EXPECT_EQ(board.getTile(calculatedPath.steps.back()).getBiome(), biome);
}

TEST(PathTo, PathToBiomeNoCostFar){
    TileGen tileGen;
    auto start = std::make_pair(0,0);
    int biome = tileGen.mountains;
    int feature = -1;
    bool ignoreTravelCost = true;
    int maxDistance = 25;
    int toSkip = 0;

    int expectedTilesTraversed = 10;

    Board board = load("pathTo", start);
    auto calculatedPath = board.pathTo(start, biome, feature, ignoreTravelCost, maxDistance, toSkip);

    EXPECT_EQ(calculatedPath.tilesTraversed, expectedTilesTraversed);
    EXPECT_EQ(board.getTile(calculatedPath.steps.back()).getBiome(), biome);
}

TEST(PathTo, PathToBiomeNoCostCannotFind){
    TileGen tileGen;
    auto start = std::make_pair(0,0);
    int biome = tileGen.ocean;
    int feature = -1;
    bool ignoreTravelCost = true;
    int maxDistance = 100;
    int toSkip = 0;

    int expectedTilesTraversed = -1;

    Board board = load("pathTo", start);
    auto calculatedPath = board.pathTo(start, biome, feature, ignoreTravelCost, maxDistance, toSkip);

    EXPECT_EQ(calculatedPath.tilesTraversed, expectedTilesTraversed);
}
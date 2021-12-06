#include "../submodules/googletest/googletest/include/gtest/gtest.h"
#include "../src/board.h"

TEST(PathTo, PathToCoordinatesNoCost){
    Board board(7);
    auto start = std::make_pair(0,0);
    auto end = std::make_pair(3,5);
    int biome = -1;
    int feature = -1;
    bool ignoreTravelCost = true;
    int maxDistance = 25;
    int toSkip = 0;

    int expectedTilesTraversed = 8;
    auto expectedDestination = std::make_pair(3,5);

    auto calculatedPath = board.pathTo(start, biome, feature, ignoreTravelCost, maxDistance, toSkip, end);

    EXPECT_EQ(calculatedPath.tilesTraversed, expectedTilesTraversed);
    EXPECT_EQ(calculatedPath.steps.back().first, expectedDestination.first);
    EXPECT_EQ(calculatedPath.steps.back().second, expectedDestination.second);
}

TEST(PathTo, PathToCoordinatesNoCostBrokenDistance){
    Board board(7);
    auto start = std::make_pair(0,0);
    auto end = std::make_pair(3,5);
    int biome = -1;
    int feature = -1;
    bool ignoreTravelCost = true;
    int maxDistance = 1;
    int toSkip = 0;

    int expectedTilesTraversed = -1;

    auto calculatedPath = board.pathTo(start, biome, feature, ignoreTravelCost, maxDistance, toSkip, end);

    EXPECT_EQ(calculatedPath.tilesTraversed, expectedTilesTraversed);
}

TEST(PathTo, PathToCoordinatesNoCostUselessSkip){
    Board board(7);
    auto start = std::make_pair(0,0);
    auto end = std::make_pair(3,5);
    int biome = -1;
    int feature = -1;
    bool ignoreTravelCost = true;
    int maxDistance = 25;
    int toSkip = 9;

    int expectedTilesTraversed = 8;
    auto expectedDestination = std::make_pair(3,5);

    auto calculatedPath = board.pathTo(start, biome, feature, ignoreTravelCost, maxDistance, toSkip, end);

    EXPECT_EQ(calculatedPath.tilesTraversed, expectedTilesTraversed);
    EXPECT_EQ(calculatedPath.steps.back().first, expectedDestination.first);
    EXPECT_EQ(calculatedPath.steps.back().second, expectedDestination.second);
}

TEST(PathTo, PathToBiomeNoCostClose){
    Board board(7);
    TileGen tileGen;
    auto start = std::make_pair(0,0);
    int biome = tileGen.plains;
    int feature = -1;
    bool ignoreTravelCost = true;
    int maxDistance = 25;
    int toSkip = 0;

    int expectedTilesTraversed = 1;

    auto calculatedPath = board.pathTo(start, biome, feature, ignoreTravelCost, maxDistance, toSkip);

    EXPECT_EQ(calculatedPath.tilesTraversed, expectedTilesTraversed);
    EXPECT_EQ(board.getTile(calculatedPath.steps.back()).getBiome(), biome);
}

TEST(PathTo, PathToBiomeNoCostFar){
    Board board(7);
    TileGen tileGen;
    auto start = std::make_pair(0,0);
    int biome = tileGen.mountains;
    int feature = -1;
    bool ignoreTravelCost = true;
    int maxDistance = 25;
    int toSkip = 0;

    int expectedTilesTraversed = 10;

    auto calculatedPath = board.pathTo(start, biome, feature, ignoreTravelCost, maxDistance, toSkip);

    EXPECT_EQ(calculatedPath.tilesTraversed, expectedTilesTraversed);
    EXPECT_EQ(board.getTile(calculatedPath.steps.back()).getBiome(), biome);
}

TEST(PathTo, PathToBiomeNoCostCannotFind){
    Board board(7);
    TileGen tileGen;
    auto start = std::make_pair(0,0);
    int biome = tileGen.ocean;
    int feature = -1;
    bool ignoreTravelCost = true;
    int maxDistance = 100;
    int toSkip = 0;

    int expectedTilesTraversed = -1;

    auto calculatedPath = board.pathTo(start, biome, feature, ignoreTravelCost, maxDistance, toSkip);

    EXPECT_EQ(calculatedPath.tilesTraversed, expectedTilesTraversed);
}
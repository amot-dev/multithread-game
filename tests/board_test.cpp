#include <gtest/gtest.h>
#include "../src/board.h"
#include "../src/interface.h"
#include "../src/utility.h"

class PathToEnvironment : public ::testing::Environment {
public:
    void SetUp() override {
        Board board = load("pathTo", std::make_pair(0,0));
        Interface interface;
        std::cout << "Test Board:" << std::endl;
        interface.printGame(board, std::make_pair(0,0), false);
    }
};

testing::Environment* const foo_env = testing::AddGlobalTestEnvironment(new PathToEnvironment);

struct TestPathToDefaults{
    std::pair<int,int> start = std::make_pair(0,0);
    std::pair<int,int> end = std::make_pair(0,0);
    int biome = -1;
    int feature = -1;
    bool ignoreTravelCost = true;
    int maxDistance = 25;
    int toSkip = 0;
};

TEST(PathToNoCost, Coordinates){
    TestPathToDefaults p;
    p.end = std::make_pair(3,5);

    int expectedTilesTraversed = 8;
    auto expectedDestination = std::make_pair(3,5);

    Board board = load("pathTo", p.start);
    auto calculatedPath = board.pathTo(p.start, p.biome, p.feature, p.ignoreTravelCost, p.maxDistance, p.toSkip, p.end);

    EXPECT_EQ(calculatedPath.tilesTraversed, expectedTilesTraversed);
    EXPECT_EQ(calculatedPath.steps.back().first, expectedDestination.first);
    EXPECT_EQ(calculatedPath.steps.back().second, expectedDestination.second);
}

TEST(PathToNoCost, CoordinatesBrokenDistance){
    TestPathToDefaults p;
    p.end = std::make_pair(3,5);
    p.maxDistance = 1;

    int expectedTilesTraversed = -1;

    Board board = load("pathTo", p.start);
    auto calculatedPath = board.pathTo(p.start, p.biome, p.feature, p.ignoreTravelCost, p.maxDistance, p.toSkip, p.end);

    EXPECT_EQ(calculatedPath.tilesTraversed, expectedTilesTraversed);
}

TEST(PathToNoCost, CoordinatesUselessSkip){
    TestPathToDefaults p;
    p.end = std::make_pair(3,5);
    p.toSkip = 9;

    int expectedTilesTraversed = 8;
    auto expectedDestination = std::make_pair(3,5);

    Board board = load("pathTo", p.start);
    auto calculatedPath = board.pathTo(p.start, p.biome, p.feature, p.ignoreTravelCost, p.maxDistance, p.toSkip, p.end);

    EXPECT_EQ(calculatedPath.tilesTraversed, expectedTilesTraversed);
    EXPECT_EQ(calculatedPath.steps.back().first, expectedDestination.first);
    EXPECT_EQ(calculatedPath.steps.back().second, expectedDestination.second);
}

TEST(PathToNoCost, Biome){
    TestPathToDefaults p;
    TileGen tileGen;
    p.biome = tileGen.plains;

    int expectedTilesTraversed = 1;

    Board board = load("pathTo", p.start);
    auto calculatedPath = board.pathTo(p.start, p.biome, p.feature, p.ignoreTravelCost, p.maxDistance, p.toSkip);

    EXPECT_EQ(calculatedPath.tilesTraversed, expectedTilesTraversed);
    EXPECT_EQ(board.getTile(calculatedPath.steps.back()).getBiome(), p.biome);
}

TEST(PathToNoCost, BiomeSkip){
    TestPathToDefaults p;
    TileGen tileGen;
    p.biome = tileGen.plains;
    p.toSkip = 7;

    int expectedTilesTraversed = 3;

    Board board = load("pathTo", p.start);
    auto calculatedPath = board.pathTo(p.start, p.biome, p.feature, p.ignoreTravelCost, p.maxDistance, p.toSkip);

    EXPECT_EQ(calculatedPath.tilesTraversed, expectedTilesTraversed);
    EXPECT_EQ(board.getTile(calculatedPath.steps.back()).getBiome(), p.biome);
}

TEST(PathToNoCost, BiomeFar){
    TestPathToDefaults p;
    TileGen tileGen;
    p.biome = tileGen.mountains;

    int expectedTilesTraversed = 10;

    Board board = load("pathTo", p.start);
    auto calculatedPath = board.pathTo(p.start, p.biome, p.feature, p.ignoreTravelCost, p.maxDistance, p.toSkip);

    EXPECT_EQ(calculatedPath.tilesTraversed, expectedTilesTraversed);
    EXPECT_EQ(board.getTile(calculatedPath.steps.back()).getBiome(), p.biome);
}

TEST(PathToNoCost, BiomeCannotFind){
    TestPathToDefaults p;
    TileGen tileGen;
    p.biome = tileGen.ocean;
    p.maxDistance = 100;

    int expectedTilesTraversed = -1;

    Board board = load("pathTo", p.start);
    auto calculatedPath = board.pathTo(p.start, p.biome, p.feature, p.ignoreTravelCost, p.maxDistance, p.toSkip);

    EXPECT_EQ(calculatedPath.tilesTraversed, expectedTilesTraversed);
}

TEST(PathToNoCost, Feature){
    TestPathToDefaults p;
    FeatureGen featGen;
    p.feature = featGen.lake;

    int expectedTilesTraversed = 11;

    Board board = load("pathTo", p.start);
    auto calculatedPath = board.pathTo(p.start, p.biome, p.feature, p.ignoreTravelCost, p.maxDistance, p.toSkip);

    EXPECT_EQ(calculatedPath.tilesTraversed, expectedTilesTraversed);
    EXPECT_EQ(board.getTile(calculatedPath.steps.back()).getFeature(), p.feature);
}

TEST(PathToNoCost, FeatureSkip){
    TestPathToDefaults p;
    FeatureGen featGen;
    p.feature = featGen.lake;
    p.toSkip = 3;

    int expectedTilesTraversed = 15;

    Board board = load("pathTo", p.start);
    auto calculatedPath = board.pathTo(p.start, p.biome, p.feature, p.ignoreTravelCost, p.maxDistance, p.toSkip);

    EXPECT_EQ(calculatedPath.tilesTraversed, expectedTilesTraversed);
    EXPECT_EQ(board.getTile(calculatedPath.steps.back()).getFeature(), p.feature);
}

TEST(PathToNoCost, FeatureNone){
    TestPathToDefaults p;
    FeatureGen featGen;
    p.feature = featGen.none;

    int expectedTilesTraversed = 1;

    Board board = load("pathTo", p.start);
    auto calculatedPath = board.pathTo(p.start, p.biome, p.feature, p.ignoreTravelCost, p.maxDistance, p.toSkip);

    EXPECT_EQ(calculatedPath.tilesTraversed, expectedTilesTraversed);
    EXPECT_EQ(board.getTile(calculatedPath.steps.back()).getFeature(), p.feature);
}

TEST(PathToNoCost, FeatureAny){
    TestPathToDefaults p;
    FeatureGen featGen;
    p.feature = featGen.any;

    int expectedTilesTraversed = 4;

    Board board = load("pathTo", p.start);
    auto calculatedPath = board.pathTo(p.start, p.biome, p.feature, p.ignoreTravelCost, p.maxDistance, p.toSkip);

    EXPECT_EQ(calculatedPath.tilesTraversed, expectedTilesTraversed);
    EXPECT_EQ(board.getTile(calculatedPath.steps.back()).getFeature(), featGen.camp);
}

TEST(PathToNoCost, FeatureAnySkip){
    TestPathToDefaults p;
    FeatureGen featGen;
    p.feature = featGen.any;
    p.toSkip = 31;

    int expectedTilesTraversed = 20;

    Board board = load("pathTo", p.start);
    auto calculatedPath = board.pathTo(p.start, p.biome, p.feature, p.ignoreTravelCost, p.maxDistance, p.toSkip);

    EXPECT_EQ(calculatedPath.tilesTraversed, expectedTilesTraversed);
    EXPECT_EQ(board.getTile(calculatedPath.steps.back()).getFeature(), featGen.cityPrison);
}

TEST(PathToNoCost, FeatureAnyCannotFind){
    TestPathToDefaults p;
    FeatureGen featGen;
    p.feature = featGen.any;
    p.maxDistance = 19;
    p.toSkip = 31;

    int expectedTilesTraversed = -1;

    Board board = load("pathTo", p.start);
    auto calculatedPath = board.pathTo(p.start, p.biome, p.feature, p.ignoreTravelCost, p.maxDistance, p.toSkip);

    EXPECT_EQ(calculatedPath.tilesTraversed, expectedTilesTraversed);
}
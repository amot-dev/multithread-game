#ifndef TILE
#define TILE

#include <map>
#include <cereal/archives/json.hpp>
#include "board.h"

class Board;

/**
 * @brief Defines some useful values used in tile generation
 * 
 */
struct TileGen{
    /** Names of all biomes currently used */
    enum biomes {plains, forest, ocean, desert, mountains};
    /** Defines minimum biome size */
    const int minBiomeSize = 2;
    /** Defines max biome size */
    const int maxBiomeSize = 5;
    /** Defines chances for each biome to generate */
    const std::map<int,double> biomeChances = {
        {plains,0.25},
        {forest,0.35},
        {ocean,0.2},
        {desert,0.1},
        {mountains,0.1}
    };
    /** Defines travel costs for each biome */
    const std::map<int,int> biomeTravelCosts = {
        {plains,2},
        {forest,5},
        {ocean,1000},
        {desert,3},
        {mountains,1000}
    };
};

/**
 * @brief Defines some useful values used in feature generation
 * 
 */
struct FeatureGen{
    /** Names of all features currently used */
    enum features {none, any, city, cityMarket, cityHarbour, cityPlaza, cityArena, cityPrison, cityNeighbourhood,
        village, camp, loneHouse, cave, lake};
    /** Defines chance for any feature to generate */
    const double featureChance = 0.05;
    /** Defines chances for each feature to generate */
    const std::map<int, double> featureChances = {
        {city, 0.10},
        {village, 0.20},
        {camp, 0.25},
        {loneHouse, 0.1},
        {cave, 0.15},
        {lake, 0.20}
    };

    /**
     * @brief Defines chances for ADDITIONAL district to generate
     * 
     * When a city is generated, a random amount of districts will
     * be generated. The main tile will be "city". The second tile
     * will always be "market". The third tile will be "harbour" if
     * the city borders an ocean, otherwise a random tile will be
     * picked from below. The fourth tile will always be a "gate".
     * Cities with gates are walled and can only be entered by the
     * gate. Subsequent districts are all chosen from below. Certain
     * districts are unique (harbour, arena, prison). They are removed
     * from the odds if they already exist. 
     */
    const std::map<int, double> cityDistrictChances = {
        {cityMarket, 0.1},
        {cityPlaza, 0.3},
        {cityArena, 0.1},
        {cityPrison, 0.3},
        {cityNeighbourhood, 0.2}
    };
    /** Defines minimum number of districts a city will generate */
    const int minCityDistricts = 2;
    /** Defines maximum number of districts a city will generate */
    const int maxCityDistricts = 9;
};

/**
 * @brief Contains all information relating to a tile
 * 
 */
class Tile{
    /** A pointer to the board the tile is on */
    Board* board;
    /** The coordinates of the tile */
    std::pair<int,int> coordinates;
    /** The tile ready status. True when the tile is fully generated */
    bool ready;
    /** The biome at the tile */
    int biome;
    /** The feature at the tile */
    int feature;
    /** The cost of traversing the tile */
    int travelCost;
public:
    /**
     * @brief Construct a new Tile object (default constructor)
     * 
     * The default constructor is required to deserialize the Tile object
     */
    Tile();

    /**
     * @brief Create a new tile at the coordinates
     * 
     * @param board The board the tile is on
     * @param coordinates The location of the tile
     */
    Tile(Board* board, std::pair<int,int> coordinates);

    /**
     * @brief Create a new unfinished tile and set it to a biome
     * 
     * @param board The board the tile is on
     * @param biome The biome to initialize the tile with
     */
    Tile(Board* board, int biome);

    /**
     * @brief Allows serialization of Tile class
     * 
     * @tparam Archive 
     * @param archive 
     */
    template<class Archive>
    void serialize(Archive& archive){
        archive(
            cereal::make_nvp("Ready",ready),
            cereal::make_nvp("Biome",biome),
            cereal::make_nvp("Feature",feature),
            cereal::make_nvp("Travel Cost",travelCost)
        );
    }

    /**
     * @brief Get the biome of the tile
     * 
     * @return Biome
     */
    int getBiome() const;

    /**
     * @brief Set the feature of the tile
     * 
     * @param newFeature Feature to set
     */
    void setFeature(int newFeature);

    /**
     * @brief Get the feature of the tile
     * 
     * @return Feature 
     */
    int getFeature() const;

    /**
     * @brief Get the travel cost of the tile
     * 
     * @return Travel cost 
     */
    int getTravelCost() const;

    /**
     * @brief Return whether or not the tile can be traversed
     * 
     * @return Whether or not the tile can be traversed 
     */
    bool isTravellable() const;

    /**
     * @brief Return the ready status of the tile
     * 
     * @return Ready status
     */
    bool isReady() const;

    /**
     * @brief Generates biome around this tile
     * 
     * This function essentially generates biomes in "splotches".
     * After setting the biome for the current tile, it checks
     * which direction it can generate a new biome into. It
     * then moves in that direction a random amount (this
     * amount is determined by min and max biome size), and
     * generates a splotch a random number of tiles in each
     * direction, ensuring to cover the current tile too.
     * 
     */
    void generateBiome();

    /**
     * @brief Generates feature at the given coordinates
     * 
     * For most features this is straightforward. Cities however
     * are multi-tile and will sometimes overwrite nearby features
     * or even generate new tiles for the rest of the city
     * to generate.
     * 
     */
    void generateFeature();
};

#endif
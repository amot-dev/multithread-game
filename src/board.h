#ifndef BOARD
#define BOARD

#include <map>
#include <unordered_set>
#include <vector>
#include <cereal/archives/json.hpp>
#include "tile.h"

class Tile;

/**
 * @brief Construct used to contain all data related to a path between two tiles
 * 
 */
struct Path{
    /** The tiles traversed on the path */
    int tilesTraversed = 0;
    /** The cost of travelling the path */
    int travelCost = 0;
    /** A vector of all the steps taken on the path */
    std::vector<std::pair<int,int>> steps;
};

/**
 * @brief Generates and manages the game board
 * 
 */
class Board{
    /** The amount of the world that's viewed (and generated at once) */
    static const int viewSize = 21;
    /** Map of coordinates to tiles, contains the world */
    std::map<std::pair<int,int>, Tile> world;
    /** Seed used in generation of the world */
    int seed;

    /**
     * @brief Generates the world on first load
     * 
     */
    void generateBoard();

    /**
     * @brief Implements travel cost comparison for tiles by coordinate
     * 
     */
    class CompareTravelCost{
    public:
        /**
         * @brief Implements travel cost comparison for tiles by coordinate
         * 
         * @param lhs The coordinate left of the operator
         * @param rhs The coordinate right of the operator
         * @return True if rhs > lhs
         */
        bool operator()(const std::pair<std::pair<int,int>,Path>& lhs, const std::pair<std::pair<int,int>,Path>& rhs) const;
    };

public:
    /**
     * @brief Build new world centered at 0,0
     * 
     */
    Board();

    /**
     * @brief Build new world with specified seed centered at 0,0
     * 
     * @param seed Seed to use in generation
     */
    Board(int seed);

    /**
     * @brief Destroy the Board object (default deconstructor)
     * 
     */
    ~Board();

    /**
     * @brief Allows serialization of board class
     * 
     * @tparam Archive 
     * @param archive 
     */
    template<class Archive>
    void serialize(Archive& archive){
        archive(
            cereal::make_nvp("Seed",seed),
            cereal::make_nvp("Board",world)
        );
    }

    /**
     * @brief Get the board's view size
     * 
     * @return Board's view size
     */
    int getViewSize() const;

    /**
     * @brief Get the world's seed
     * 
     * @return Board's seed
     */
    int getSeed() const;

    /**
     * @brief Check if the given coordinates contain a generated tile
     * 
     * @param coordinates x,y pair of coordinates
     * @return Whether or not the specified coordinates contain a generated tile 
     */
    bool tileExists(std::pair<int,int> coordinates) const;

    /**
     * @brief Get the tile at the coordinates
     * 
     * @param coordinates Location of desired tile
     * @return Tile at coordinates
     */
    Tile getTile(std::pair<int,int> coordinates) const;

    /**
     * @brief Set the tile at the coordinates
     * 
     * @param coordinates Location of desired tile
     * @param tile Tile to set
     * @return Whether the tile was generated
     */
    bool setTile(std::pair<int,int> coordinates, Tile tile);

    /**
     * @brief Verify world integrity
     * 
     * @param position Position to verify around
     * @return Whether or not the world is valid for play
     */
    bool verify(std::pair<int,int> position) const;

    /**
     * @brief Generates a path between a starting coordinates and some tile, up to a maximum distance
     * 
     * Uses a BFS algorithm to find the shortest path between two tiles. If both biome and feature are -1,
     * the algorithm searches by coordinates. Otherwise it tries to match biome and/or feature.
     *
     * @param start Starting position
     * @param biome Biome to look for (-1 to ignore)
     * @param feature Feature to look for (-1 to ignore)
     * @param ignoreTravelCost Whether or not to ignore travel cost
     * @param maxDistance Maximum distance to search (implemented as tiles or distance depending on ignoreTravelCost)
     * @param toSkip How many matches to ignore (does nothing if coordinates specified)
     * @param end End position (if coordinates are known)
     * @return A path between the starting coordinates and the nth matching tile, where n is toSkip + 1
     */
    Path pathTo(
        std::pair<int,int> start,
        int biome,
        int feature,
        bool ignoreTravelCost,
        int maxDistance,
        int toSkip,
        std::pair<int,int> end = std::make_pair(0,0)
    ) const;
};

#endif
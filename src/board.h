#ifndef BOARD
#define BOARD

#include <map>
#include <unordered_set>
#include <vector>
#include <cereal/archives/json.hpp>
#include "tile.h"

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
    /** The amount of the board that's viewed (and generated at once) */
    static const int viewSize = 21;
    /** Map of coordinates to tiles, contains the board */
    std::map<std::pair<int,int>, Tile> board;
    /** Seed used in generation of the board */
    int seed;

    /**
     * @brief Generates the board on first load
     * 
     */
    void generateBoard();

    /**
     * @brief Generate tile at the given coordinates
     * 
     * @param coordinates x,y pair of coordinates
     */
    void generateTile(std::pair<int, int> coordinates);

    /**
     * @brief Generates biome from the given coordinates
     * 
     * This function essentially generates biomes in "splotches".
     * For a given coordinate, if there is no biome present,
     * it checks direction it can generate a new biome into.
     * It then moves in that direction a random amount (this
     * amount is determined by min and max biome size), and
     * generates a splotch a random number of tiles in each
     * direction, ensuring to cover the original coordinates
     * too.
     * 
     * @param coordinates x,y pair of coordinates
     */
    void generateBiome(std::pair<int, int> coordinates);

    /**
     * @brief Generates feature at the given coordinates
     * 
     * For most features this is straightForward. Cities however
     * are multi-tile and will sometimes overwrite nearby features
     * or even generate new tiles for the rest of the city
     * to generate.
     * 
     * @param coordinates x,y pair of coordinates
     */
    void generateFeature(std::pair<int, int> coordinates);

    /**
     * @brief Check if the given coordinates contain a generated tile
     * 
     * @param coordinates x,y pair of coordinates
     * @return Whether or not the specified coordinates contain a generated tile 
     */
    bool tileExists(std::pair<int,int> coordinates) const;

    /**
     * @brief Check if the given coordinates contain a ready tile
     * 
     * @param coordinates x,y pair of coordinates
     * @return Whether or not the specified coordinates contain a ready tile 
     */
    bool tileReady(std::pair<int,int> coordinates) const;

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
     * @brief Build new board centered at 0,0
     * 
     */
    Board();

    /**
     * @brief Build new board with specified seed centered at 0,0
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
            cereal::make_nvp("Board",board)
        );
    }

    /**
     * @brief Get the board's view size
     * 
     * @return Board's view size
     */
    int getViewSize() const;

    /**
     * @brief Get the board's seed
     * 
     * @return Board's seed
     */
    int getSeed() const;

    /**
     * @brief Get the tile at the coordinates
     * 
     * @param coordinates Location of desired tile
     * @return Tile at coordinates
     */
    Tile getTile(std::pair<int,int> coordinates) const;

    /**
     * @brief Verify board integrity
     * 
     * @param position Position to verify around
     * @return Whether or not the board is valid for play
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
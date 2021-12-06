#ifndef BOARD
#define BOARD

#include <map>
#include <unordered_set>
#include <vector>
#include "tile.h"

/** Construct used to contain all data related to a path between two tiles */
struct Path{
    int tilesTraversed = 0;
    int travelCost = 0;
    std::vector<std::pair<int,int>> steps;
};

/** Generates and manages the game board  */ 
class Board{
    static const int viewSize = 21;
    std::map<std::pair<int,int>, Tile> board;
    int seed;

    /** Generates the board on first load
    *
    */
    void generateBoard();

    /** Generate tile at the given coordinates
    *
    * @param coordinates x,y pair of coordinates
    */
    void generateTile(std::pair<int, int> coordinates);

    /** Generates biome from the given coordinates
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

    /** Generates feature at the given coordinates
    * 
    * For most features this is straightForward. Cities however
    * are multi-tile and will sometimes overwrite nearby features
    * or even generate new tiles for the rest of the city
    * to generate.
    *
    * @param coordinates x,y pair of coordinates
    */
    void generateFeature(std::pair<int, int> coordinates);

    /** Check if the given coordinates contain a generated tile
    *
    * @param coordinates x,y pair of coordinates
    * @return Whether or not the specified coordinates contain a generated tile
    */
    bool tileExists(std::pair<int,int> coordinates) const;

    /** Check if the given coordinates contain a ready tile
    *
    * @param coordinates x,y pair of coordinates
    * @return Whether or not the specified coordinates contain a ready tile
    */
    bool tileReady(std::pair<int,int> coordinates) const;

    /** Generates a vector of coordinates in a radius around some coordinates
    *
    * @param coordinates x,y pair of coordinates
    * @param radius Radius to look around
    * @return A vector containing the requested coordinates
    */
    std::vector<std::pair<int,int>> getCoordinatesInRadius(std::pair<int,int> coordinates, int radius) const;

    /** Generates a vector of coordinates in a ring at a radius around some coordinates
    *
    * @param coordinates x,y pair of coordinates
    * @param radius Radius of ring to look at
    * @return A vector containing the requested coordinates
    */
    std::vector<std::pair<int,int>> getCoordinatesInRing(std::pair<int,int> coordinates, int radius) const;

    /** Generates a vector of coordinates adjacent some coordinates
    *
    * Here, diagonal connections are not considered adjacent since
    * diagonal moves are not allowed
    * 
    * @param coordinates x,y pair of coordinates
    * @return A vector containing the requested coordinates
    */
    std::vector<std::pair<int,int>> getAdjacentCoordinates(std::pair<int,int> coordinates) const;

    /** Implements travel cost comparison for tiles by coordinate */
    class CompareTravelCost{
    public:
        /** Implements travel cost comparison for tiles by coordinate
        *
        * @param lhs The coordinate left of the operator
        * @param rhs The coordinate right of the operator
        * @return True if rhs > lhs
        */
        bool operator()(const std::pair<std::pair<int,int>,Path>& lhs, const std::pair<std::pair<int,int>,Path>& rhs) const;
    };

public:
    /** Build new board centered at 0,0
    *
    */
    Board();

    /** Build new board with specified seed centered at 0,0
    *
    * @param seed Seed to use in generation
    */
    Board(int seed);

    /** Load board
    *
    * @param seed Seed to use in further generation
    * @param loadBoard Board to load (must be at least viewSize)
    * @param position Player position (used to check validity of board)
    */
    Board(int seed, std::map<std::pair<int,int>,Tile> loadBoard, std::pair<int,int> position);

    ~Board();

    /** Returns the board's view size
    *
    * @return Board's view size
    */
    int getViewSize() const;

    /** Returns the tile at the coordinates
    *
    * @param coordinates Location of desired tile
    * @return Tile at coordinates
    */
    Tile getTile(std::pair<int,int> coordinates) const;

    /** Generates a path between a starting coordinates and some tile, up to a maximum distance
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
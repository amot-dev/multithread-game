#ifndef BOARD
#define BOARD

#include <map>
#include <vector>
#include "tile.h"

/** Construct used to contain all data related to a path between two tiles */
struct Path{
    int tiles;
    int travelCost;
};

/** Generates and manages the game board  */ 
class Board{
    const int viewSize = 15;
    TileGen tileGen;
    FeatureGen featGen;
    std::map<std::pair<int,int>, Tile> board;

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

    /** Generates a path between two coordinates on the board, up to a maximum distance
    *
    * @param position Starting position
    * @param coordinates Ending Position
    * @param maxDistance Maximum distance to search
    * @return A path between the two coordinates
    */
    Path pathTo(std::pair<int,int> position, std::pair<int,int> coordinates, int maxDistance) const;

    /** Generates a path between a starting coordinates and some tile, up to a maximum distance
    *
    * @param position Starting position
    * @param biome Biome to look for (-1 to ignore)
    * @param feature Feature to look for (-1 to ignore)
    * @param maxDistance Maximum distance to search
    * @param toSkip How many occurences to ignore before "finding" tile
    * @return A path between the starting coordinates and the nth matching tile, where n is toSkip + 1
    */
    Path pathTo(std::pair<int,int> position, int biome, int feature, int maxDistance, int toSkip) const;

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
};

#endif
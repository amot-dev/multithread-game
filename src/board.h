#ifndef BOARD
#define BOARD

#include <map>
#include "tile.h"

/** Generates and manages the game board  */ 
class Board{
    const int viewSize = 15;
    TileGen tileGen;
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
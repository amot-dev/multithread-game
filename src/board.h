#ifndef BOARD
#define BOARD

#include <map>
/** Generates and manages the game board  */ 
class Board{
    const int viewSize = 21;

    /** Contains all information relating to a tile */
    struct Tile{
        bool ready = false;
        int biome;
    };

    /** Defines some useful values used in tile generation */
    struct TileGen{
        /** Names of all biomes currently used*/
        enum biomes {
            plains,
            forest,
            ocean,
            desert,
            mountains
        };
        /** Defines minimum biome size */
        const int minBiomeSize = 2;
        /** Defines max biome size */
        const int maxBiomeSize = 5;
        /** Defines some useful values used in tile generation */
        const std::map<int,double> biomeChances = {
            {plains,0.25},
            {forest,0.35},
            {ocean,0.2},
            {desert,0.1},
            {mountains,0.1}
        };
        /** Defines the display characters for each biome */
        const std::map<int,char> biomeChars = {
            {plains,'.'},
            {forest,'&'},
            {ocean,'~'},
            {desert,'#'},
            {mountains,'^'}
        };
    };
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
    bool tileExists(std::pair<int,int> coordinates);

    /** Print the given tile
    *
    * @param tile Tile to print
    */
    void printTile(Tile tile);

public:
    /** Build new board centered at position
    *
    * @param position Player starting position
    */
    Board();
    Board(int seed);
    ~Board();

    /** Prints a human-readable board
    *
    * @param position Player position
    */
    void printBoard(std::pair<int,int> position);
};

#endif
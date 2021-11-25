#ifndef BOARD
#define BOARD

#include <map>
/** Generates and manages the game board  */ 
class Board{
    const unsigned viewableBoardSize = 21;

    /** Contains all information relating to a tile */
    struct Tile{
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
        /** Defines some useful values used in tile generation */
        std::map<int,double> biomeChances = {
            {plains,0.3},
            {forest,0.2},
            {ocean,0.2},
            {desert,0.15},
            {mountains,0.15}
        };
    };
    TileGen tileGen;
    std::map<std::pair<int,int>, Tile> board;

    /** Generate tile at the given coordinates
    *
    * @param coordinates x,y pair of coordinates
    * @return Generated tile
    */
    Tile generateTile(std::pair<int, int> coordinates);

    /** Determine the biome for a new tile
    *
    * @param coordinates x,y pair of coordinates
    * @return Biome to be used for new tile
    */
    int determineBiomeForNewTile(std::pair<int, int> coordinates);

    /** Get weight of biome from nearby occurences
    *
    * This value is used to find the probability of generating each biome
    * 
    * @param biome Biome name
    * @param nearbyOccurences Number of occurences around the current coordinates
    * @return Weighted value for biome generation
    */
    double getBiomeWeight(int biome, int nearbyOccurences);

    /** Check if the given coordinates contain a generated tile
    *
    * @param coordinates x,y pair of coordinates
    * @return Whether or not the specified coordinates contain a generated tile
    */
    bool tileExists(std::pair<int,int> coordinates);

public:
    /** Build new board centered at position
    *
    * @param position Player starting position
    */
    Board(std::pair<int, int> position);
    ~Board();

    /** Prints a human-readable board
    *
    * @param position Player position
    */
    void printBoard(std::pair<int,int> position);
};

#endif
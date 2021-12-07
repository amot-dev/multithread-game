#ifndef INTERFACE
#define INTERFACE

#include "board.h"
#include "tile.h"

/**
 * @brief Interfaces between the Board, Player, and human
 * 
 */
class Interface{
    TileGen tileGen;
    FeatureGen featGen;

    /** Defines the amount of spacing to insert before the status */
    int statusSpacingAmount = 20;
    /** String containing spacing to insert before the status */
    std::string statusSpacing = "";
    /** Defines the display character for the player location */
    std::string playerChar = "\u263A";
    /** Defines the display characters for each biome */
    const std::map<int,std::string> biomeChars = {
        {tileGen.plains,"\u169A"},
        {tileGen.forest, "\u2E19"},
        {tileGen.ocean,"\u23D6"},
        {tileGen.desert,"."},
        {tileGen.mountains,"\u1A0F"}
    };
    /** Defines the display characters for each feature */
    const std::map<int,std::string> featureChars = {
        {featGen.city,"\u25A3"},
        {featGen.cityMarket,"\u2696"},
        {featGen.cityHarbour,"\u2693"},
        {featGen.cityPlaza,"\u2698"},
        {featGen.cityArena,"\u2694"},
        {featGen.cityPrison,"\u2162"},
        {featGen.cityNeighbourhood,"\u2302"},
        {featGen.village,"\u2C26"},
        {featGen.camp,"\u15D7"},
        {featGen.loneHouse,"\u2302"},
        {featGen.cave,"\u26CF"},
        {featGen.lake,"o"},
    };
public:
    /**
     * @brief Construct a new Interface object (default constructor)
     * 
     */
    Interface();

    /**
     * @brief Changes the spacing between the board and status
     * 
     * @param spacingAmount The value to change the spacing to
     */
    void setStatusSpacingAmount(int spacingAmount);

    /**
     * @brief Prints a human-readable board
     * 
     * @param board Board to print
     * @param position Player position
     */
    void printGame(const Board& board, std::pair<int,int> position) const;
};

#endif
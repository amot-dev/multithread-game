#ifndef INTERFACE
#define INTERFACE

#include "board.h"
#include "tile.h"

class Interface{
    TileGen tileGen;
    /** Defines the amount of spacing to insert before the status */
    int statusSpacingAmount = 20;
    /** String containing spacing to insert before the status */
    std::string statusSpacing = "";
    /** Defines the display characters for each biome */
    const std::map<int,char> biomeChars = {
        {tileGen.plains,'.'},
        {tileGen.forest,'&'},
        {tileGen.ocean,'~'},
        {tileGen.desert,'#'},
        {tileGen.mountains,'^'}
    };
public:
    /** Initializes the interface
    *
    */
    Interface();

    /** Changes the spacing between the board and status
    *
    * @param spacingAmount The value to change the spacing to
    */
    void setStatusSpacingAmount(int spacingAmount);

    /** Prints a human-readable board
    *
    * @param board Board to print
    * @param position Player position
    */
    void printGame(const Board& board, std::pair<int,int> position) const;
};

#endif
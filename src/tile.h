#ifndef TILE
#define TILE

#include <map>

/** Defines some useful values used in tile generation */
struct TileGen{
    /** Names of all biomes currently used*/
    enum biomes {plains, forest, ocean, desert, mountains};
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
};

/** Contains all information relating to a tile */
class Tile{
    bool ready;
    int biome;
public:
    /** Create a new tile and set it to a biome
    *
    * @param biome The biome to initialize the tile with
    */
    Tile(int biome);

    /** Return the biome of the tile
    *
    * @return Biome
    */
    int getBiome() const;

    /** Return the ready status of the tile
    *
    * @return Ready status
    */
    bool isReady() const;
};

#endif
#include "tile.h"

Tile::Tile(int biome):biome(biome){}

int Tile::getBiome() const {return biome;}

bool Tile::isReady() const {return ready;}
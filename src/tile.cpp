#include "tile.h"

Tile::Tile(int biome):biome(biome){}

int Tile::getBiome() const {return biome;}

void Tile::setFeature(int newFeature){feature = newFeature;}

int Tile::getFeature() const {return feature;}

bool Tile::isReady() const {return ready;}
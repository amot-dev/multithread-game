#include "tile.h"

#include "global.h"

Tile::Tile(int biome) : biome(biome){
    feature = featGen.none;
    travelCost = tileGen.biomeTravelCosts.at(biome);
}

int Tile::getBiome() const {return biome;}

void Tile::setFeature(int newFeature){feature = newFeature;}

int Tile::getFeature() const {return feature;}

int Tile::getTravelCost() const {return travelCost;}

bool Tile::isTravellable() const {
    if (tileGen.biomeTravelCosts.at(biome) == 1000) return false;
    else return true;
}

bool Tile::isReady() const {return ready;}
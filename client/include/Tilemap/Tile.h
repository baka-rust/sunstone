#ifndef TILE_H
#define TILE_H

#include <SFML/graphics.hpp>

#include "Tilemap/QuadTypes.h"

class Tile {
    public:
        // tile position in tiles.
        sf::vector2i pos;
    
        // quad ID of every quad.
        QuadType quads[4];
};

#endif // TILE_H
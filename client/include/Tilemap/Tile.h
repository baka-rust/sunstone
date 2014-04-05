#ifndef TILE_H
#define TILE_H

#include <Vector>

#include <SFML/graphics.hpp>

#include "Tilemap/QuadTypes.h"

class Tile {
    public:
        Tile(sf::Vector2i position, std::vector<QuadType> quads)
        : pos(position), quads(quads) {};
    
    Tile(int x, int y, std::vector<QuadType> quads)
    : Tile(sf::Vector2i(x, y), quads) {};
    
        // tile position in tiles.
        sf::Vector2i pos;
    
        // quad ID of every quad.
        std::vector<QuadType> quads;
};

#endif // TILE_H
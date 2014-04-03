#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>

#include "Tilemap/Tiles.h"
#include "Tilemap/Tile.h"

class Tilemap : public sf::Drawable, public sf::Transformable {
    public:
        Tilemap(sf::Texture texture, sf::Vector2i quadSize, int height, int width);
    
        addTile(Tile tile);
        getTile(int x, int y);
    
    private:
        sf::Texture _texture;
        sf::VertexArray _vertices;
};

#endif // TILEMAP_H
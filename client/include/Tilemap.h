#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>

#include "Tilemap/Tile.h"

class Tilemap : public sf::Drawable, public sf::Transformable {
    public:
        Tilemap(sf::Texture texture, sf::Vector2i quadSize, int height, int width);
    
        // see http://www.sfml-dev.org/tutorials/2.1/graphics-vertex-array.php
        addTile(Tile tile);
        getTile(unsigned int x, unsigned int y);
    
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    private:
        sf::Texture _texture;
        sf::VertexArray _vertices;
};

#endif // TILEMAP_H
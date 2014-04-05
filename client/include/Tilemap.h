#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>

#include "Tilemap/Tile.h"

// see http://www.sfml-dev.org/tutorials/2.1/graphics-vertex-array.php
class Tilemap : public sf::Drawable, public sf::Transformable {
    public:
        Tilemap(sf::Texture &texture, int quadSize, int height, int width);
    
        void setTile(Tile tile);
//        Tile getTile(unsigned int x, unsigned int y);
    
    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    private:
        sf::Texture _texture;
        sf::VertexArray _vertices;
    
        int _quadSize;
        int _height;
        int _width;
};

#endif // TILEMAP_H
#include "Tilemap.h"

#include <iostream>

#include <SFML/Graphics.hpp>

Tilemap::Tilemap(sf::Texture texture, sf::Vector2u quadSize, int height, int width)
: _texture(texture), _quadSize(quadSize), _height(height), _width(width) {
    _vertices.setPrimitiveType(sf::Quads);
	_vertices.resize(_width * _height * 4 * 4);
}

void Tilemap::setTile(Tile tile) {
    sf::Vertex *quad = &_vertices[(tile.pos.x + tile.pos.y * _width) * 4 * 4];
    
	// For each quad
	for(unsigned int i = 0; i < 4; i++) {
        unsigned int x = tile.pos.x;
		unsigned int y = tile.pos.y;
        
		// UV map the tile
		unsigned int u = tile.quads[i] % (_texture.getSize().x / _quadSize.x);
		unsigned int v = tile.quads[i] / (_texture.getSize().x / _quadSize.x);
        
		quad[i + 0].position = sf::Vector2f(x * _quadSize.x, y * _quadSize.y);
		quad[i + 1].position = sf::Vector2f((x + 1) * _quadSize.x, y * _quadSize.y);
		quad[i + 2].position = sf::Vector2f((x + 1) * _quadSize.x, (y + 1) * _quadSize.y);
		quad[i + 3].position = sf::Vector2f(x * _quadSize.x, (y + 1) * _quadSize.y);
        
		quad[i + 0].texCoords = sf::Vector2f(u * _quadSize.x, v * _quadSize.y);
		quad[i + 1].texCoords = sf::Vector2f((u + 1) * _quadSize.x, v * _quadSize.y);
		quad[i + 2].texCoords = sf::Vector2f((u + 1) * _quadSize.x, (v + 1) * _quadSize.y);
		quad[i + 3].texCoords = sf::Vector2f(u * _quadSize.x, (v + 1) * _quadSize.y);
	}
}

void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
	states.texture = &_texture;
	target.draw(_vertices, states);
}
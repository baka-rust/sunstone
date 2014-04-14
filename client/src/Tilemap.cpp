#include "Tilemap.h"

#include <iostream>

#include <SFML/Graphics.hpp>

Tilemap::Tilemap(sf::Texture &texture, int quadSize, int height, int width)
: _texture(texture), _quadSize(quadSize), _height(height), _width(width) {
    _vertices.setPrimitiveType(sf::Quads);
	_vertices.resize(_width * _height * 4 * 4);
}

void Tilemap::setTile(Tile tile) {
    sf::Vertex *quad = &_vertices[(tile.pos.x + tile.pos.y * _width) * 4 * 4];

    // Get the tile x & y coordinates
    unsigned int x = tile.pos.x;
    unsigned int y = tile.pos.y;

	// For each quad
	for(unsigned int i = 0; i < 4; i++) {
        // Find the quad position
        int fx;
        int fy;

        if (i == 0) {
            // top left corner
            fx = 2 * x;
            fy = 2 * y;

        } else if (i == 1) {
            // top right corner
            fx = 2 * x + 1;
            fy = 2 * y;

        } else if (i == 2) {
            // bottom left corner
            fx = 2 * x;
            fy = 2 * y + 1;

        } else if (i == 3) {
            // bottom right corner
            fx = 2 * x + 1;
            fy = 2 * y + 1;
        } else {
            // TODO throw error
            std::cerr << "this should never happen";
            fx = -1;
            fy = -1;
        }

		// UV map the tile
        unsigned int u = tile.quads[i] % (_texture.getSize().x / _quadSize);
        unsigned int v = tile.quads[i] / (_texture.getSize().x / _quadSize);

        quad[i * 4 + 0].position = sf::Vector2f((fx + 0) * _quadSize, (fy + 0) * _quadSize);
        quad[i * 4 + 1].position = sf::Vector2f((fx + 1) * _quadSize, (fy + 0) * _quadSize);
        quad[i * 4 + 2].position = sf::Vector2f((fx + 1) * _quadSize, (fy + 1) * _quadSize);
        quad[i * 4 + 3].position = sf::Vector2f((fx + 0) * _quadSize, (fy + 1) * _quadSize);

        quad[i * 4 + 0].texCoords = sf::Vector2f((u + 0) * _quadSize, (v + 0) * _quadSize);
        quad[i * 4 + 1].texCoords = sf::Vector2f((u + 1) * _quadSize, (v + 0) * _quadSize);
        quad[i * 4 + 2].texCoords = sf::Vector2f((u + 1) * _quadSize, (v + 1) * _quadSize);
        quad[i * 4 + 3].texCoords = sf::Vector2f((u + 0) * _quadSize, (v + 1) * _quadSize);
	}
}

void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
	states.texture = &_texture;
	target.draw(_vertices, states);
}

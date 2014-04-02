#ifndef TERRAIN_H
#define TERRAIN_H

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>
#include <map>
#include <math.h>

#include "Dungeon.h"

class Terrain {

    public:

        sf::Texture tileMap;
        std::vector<sf::Sprite*> tiles;
        int bottom[128][128];
        int mid[128][128];
        int top[128][128];

        Terrain();
        void generateFromSeed(int seed);
        void update(float elapsedTime);
        void draw(float cameraX, float cameraY, sf::RenderWindow *app);
        int getTile(int tileX, int tileY, std::string layer);

    private:

        Dungeon *dungeon;


};

#endif // TERRAIN_H

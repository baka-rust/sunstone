#ifndef TERRAIN_H
#define TERRAIN_H

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>
#include <map>
#include <math.h>

#include "Dungeon.h"
#include "Tilemap.h"
#include "Tilemap/TileTypes.h"

class Terrain {

    public:

        TileType physics[128][128];

        Terrain();

        void generateFromSeed(int seed);
        void buildTilemaps();

        void update(float elapsedTime);

//        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void draw(float cameraX, float cameraY, sf::RenderWindow *app);

        TileType getTile(int tileX, int tileY, std::string layer);

    private:

        Dungeon* dungeon;

        sf::Texture tiletex;

        Tilemap *complex;
        Tilemap *decoration;
        Tilemap *objects;

        int quadSize = 8;
        int height = 128;
        int width = 128;


};

#endif // TERRAIN_H

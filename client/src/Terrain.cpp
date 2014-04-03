#include "Terrain.h"

Terrain::Terrain() {

    tileMap.loadFromFile("resources/tilemap.png");

    int xMax = tileMap.getSize().x / 16;
    int yMax = tileMap.getSize().y / 16;

    for(int y = 0; y < tileMap.getSize().y; y += 16) {
        for(int x = 0; x < tileMap.getSize().x; x += 16) {
            tiles.push_back(new sf::Sprite(tileMap, sf::IntRect(x, y, 16, 16)));
        }
    }

    for(int y = 0; y < 128; y++) {
        for(int x = 0; x < 128; x++) {
            bottom[y][x] = 0;
            mid[y][x] = 0;
            top[y][x] = 0;
        }
    }

}

void Terrain::generateFromSeed(int seed) {

    dungeon = new Dungeon(128, 128, 10, 30, seed);
    dungeon->create();

    for(int y = 0; y < 128; y++) {
        for(int x = 0; x < 128; x++) {
            if(dungeon->getMid(x, y) == 1) {
                bottom[y][x] = 0;
            }
            else {
                bottom[y][x] = 1;
            }
        }
    }

    for(int y = 0; y < 128; y++) {
        for(int x = 0; x < 128; x++) {
            if(dungeon->getMid(x, y) == 0 || dungeon->getMid(x, y) == 2 || dungeon->getMid(x, y) == 3) {
                mid[y][x] = 0;
            }
            else {
                mid[y][x] = 2; // 2
            }
        }
    }

}

void Terrain::draw(float cameraX, float cameraY, sf::RenderWindow *app) {

    // camera tile culling
    int camXStart = (cameraX / 16) - 1;
    int camYStart = (cameraY / 16) - 1;

    int camXFinish = camXStart + 18;
    int camYFinish = camYStart + 18;

    if(camXStart < 0)
        camXStart = 0;
    if(camYStart < 0)
        camYStart = 0;

    if(camXFinish > 128)
        camXFinish = 128;
    if(camYFinish > 128)
        camYFinish = 128;

    for(int y = camYStart; y < camYFinish; y++) {
        for(int x = camXStart; x < camXFinish; x++) {
            tiles[bottom[y][x]]->setPosition(x*16, y*16); // kinda messy but what can you do (draw calls are saved because a singular sprite is drawn as a batch when moved)
            app->draw(*tiles[bottom[y][x]]);
        }
    }
    for(int y = camYStart; y < camYFinish; y++) {
        for(int x = camXStart; x < camXFinish; x++) {
            tiles[mid[y][x]]->setPosition(x*16, y*16);
            app->draw(*tiles[mid[y][x]]);
        }
    }

}

int Terrain::getTile(int tileX, int tileY, std::string layer) {
    return mid[tileY][tileX];
}

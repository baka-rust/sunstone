#include "Terrain.h"
#include "Tilemap.h"

Terrain::Terrain() {

    tiletex.loadFromFile("resources/tilemap.png");

//    int xMax = tileMap.getSize().x / 16;
//    int yMax = tileMap.getSize().y / 16;
    
    complex = new Tilemap(tiletex, quadSize, height, width);

//    for(int y = 0; y < 128; y++) {
//        for(int x = 0; x < 128; x++) {
//            bottom[y][x] = 0;
//            mid[y][x] = 0;
//            top[y][x] = 0;
//        }
//    }
    
    generateFromSeed(4); // TODO make sample menu dungeon
    // buildTilemaps();

}

void Terrain::generateFromSeed(int seed) {

    dungeon = new Dungeon(128, 128, 10, 30, seed);
    dungeon->create();
    
    buildTilemaps();
    
//    complex->setOrigin(64 * 16, 64 * 16);
    complex->setPosition(512, 512);
//    complex->setScale(2, 2);
    std::cout << complex->getPosition().x << std::endl;
    std::cout << "Built tilemaps!" << std::endl;
}

void Terrain::buildTilemaps() {
    for (int y = 0; y < 128; y++) {
        for(int x = 0; x < 128; x++) {
            std::vector<QuadType> quads;
            quads.reserve(4);
            
            if(dungeon->getMid(x, y) == 1) {
                quads.insert(quads.begin() + 0, tl_wall_back_horiz);
                quads.insert(quads.begin() + 1, tr_wall_back_horiz);
                quads.insert(quads.begin() + 2, bl_wall_back_horiz);
                quads.insert(quads.begin() + 3, br_wall_back_horiz);
            } else if(dungeon->getMid(x, y) == 2){
                quads.insert(quads.begin() + 0, tl_floor_dec_semi_in);
                quads.insert(quads.begin() + 1, tr_floor_dec_semi_in);
                quads.insert(quads.begin() + 2, bl_floor_dec_semi_in);
                quads.insert(quads.begin() + 3, br_floor_dec_semi_in);
            } else {
                quads.insert(quads.begin() + 0, tl_floor);
                quads.insert(quads.begin() + 1, tr_floor);
                quads.insert(quads.begin() + 2, bl_floor);
                quads.insert(quads.begin() + 3, br_floor);
            }
            
            Tile tile = Tile(x, y, quads);
            complex->setTile(tile);
        }
    }
    
//    complex->setScale(1, 1);
    
//    for(int y = 0; y < 128; y++) {
//        for(int x = 0; x < 128; x++) {
//            if(dungeon->getMid(x, y) == 1) {
//                bottom[y][x] = 0;
//            }
//            else {
//                bottom[y][x] = 1;
//            }
//        }
//    }
//    
//    for(int y = 0; y < 128; y++) {
//        for(int x = 0; x < 128; x++) {
//            if(dungeon->getMid(x, y) == 0 || dungeon->getMid(x, y) == 2 || dungeon->getMid(x, y) == 3) {
//                mid[y][x] = 0;
//            }
//            else {
//                mid[y][x] = 2; // 2
//            }
//        }
//    }

}

void Terrain::draw(float cameraX, float cameraY, sf::RenderWindow *app) {
    app->draw(*complex);
//
//    // camera tile culling
//    int camXStart = (cameraX / 16) - 1;
//    int camYStart = (cameraY / 16) - 1;
//
//    int camXFinish = camXStart + 18;
//    int camYFinish = camYStart + 18;
//
//    if(camXStart < 0)
//        camXStart = 0;
//    if(camYStart < 0)
//        camYStart = 0;
//
//    if(camXFinish > 128)
//        camXFinish = 128;
//    if(camYFinish > 128)
//        camYFinish = 128;
//
//    for(int y = camYStart; y < camYFinish; y++) {
//        for(int x = camXStart; x < camXFinish; x++) {
//            tiles[bottom[y][x]]->setPosition(x*16, y*16); // kinda messy but what can you do (draw calls are saved because a singular sprite is drawn as a batch when moved)
//            app->draw(*tiles[bottom[y][x]]);
//        }
//    }
//    for(int y = camYStart; y < camYFinish; y++) {
//        for(int x = camXStart; x < camXFinish; x++) {
//            tiles[mid[y][x]]->setPosition(x*16, y*16);
//            app->draw(*tiles[mid[y][x]]);
//        }
//    }
//
}

TileType Terrain::getTile(int tileX, int tileY, std::string layer) {
    return physics[tileY][tileX];
}

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
    
    complex->setPosition(512, 512);
    std::cout << "Built tilemaps!" << std::endl;
}

void Terrain::buildTilemaps() {
    for (int y = 0; y < 128; y++) {
        for(int x = 0; x < 128; x++) {
            std::vector<QuadType> quads;
            quads.reserve(4);
            
            if(dungeon->getMid(x, y) == 1) {
                // draw walls
                
                // check around wall to see what's wall and what's not.
                bool n  = (y == 0 || dungeon->getMid(x, y - 1) == 1);
                bool e  = (x == 127 || dungeon->getMid(x + 1, y) == 1);
                bool s  = (y == 127 || dungeon->getMid(x, y + 1) == 1);
                bool w  = (x == 0 || dungeon->getMid(x - 1, y) == 1);
                
                bool ne = (y == 0   || x == 127 || dungeon->getMid(x + 1, y - 1) == 1);
                bool nw = (y == 0   || x == 0   || dungeon->getMid(x - 1, y - 1) == 1);
                bool se = (y == 127 || x == 127 || dungeon->getMid(x + 1, y + 1) == 1);
                bool sw = (y == 127 || x == 0   || dungeon->getMid(x - 1, y + 1) == 1);
                
                
                
               
                // Top Left
                if(n && w) {
                    if(!sw && s) {
                        quads.insert(quads.begin() + 0, tl_wall_right_horiz);
                    } else {
                        if(!s) {
                            quads.insert(quads.begin() + 0, tl_wall_back_horiz);
                        } else {
                            if(!nw) {
                                // TODO bottom to side
                                quads.insert(quads.begin() + 0, tl_floor_dec_full_vert);
                            } else {
                                quads.insert(quads.begin() + 0, tl_black);
                            }
                        }
                    }
                } else {
                    if(!s) {
                        if(!w) {
                            quads.insert(quads.begin() + 0, tl_wall_back_vert);
                        } else {
                            // !s && !w
                            // TODO Duplicate/unused?
                            quads.insert(quads.begin() + 0, tl_blank);
//                            quads.insert(quads.begin() + 0, tl_wall_back_horiz);
                        }
                    } else {
                        if(!n) {
                            if(!w) {
                                // TODO side to bottom
                                quads.insert(quads.begin() + 0, tl_floor_dec_full_horiz);
                            } else {
                                quads.insert(quads.begin() + 0, tl_wall_bottom);
                            }
                        } else {
                            quads.insert(quads.begin() + 0, tl_wall_right_vert);
                        }
                    }
                }
                
                // Top right
                if(n && e) {
                    if(!se && s) {
                        quads.insert(quads.begin() + 1, tr_wall_left_horiz);
                    } else {
                        quads.insert(quads.begin() + 1, tr_black);
                    }
                } else {
                    if(!s) {
                        if(!e) {
                            quads.insert(quads.begin() + 1, tr_wall_back_vert);
                        } else {
                            quads.insert(quads.begin() + 1, tr_wall_back_horiz);
                        }
                    } else {
                        if(!n) {
                            quads.insert(quads.begin() + 1, tr_wall_bottom);
                        } else {
                            quads.insert(quads.begin() + 1, tr_wall_left_vert);
                        }
                    }
                }
                
                // Bottom left
                if(s && w) {
                    if(!sw && n) {
                        quads.insert(quads.begin() + 2, bl_wall_right_vert);
                    } else {
                        quads.insert(quads.begin() + 2, bl_black);
                    }
                } else {
                    if(!s) {
                        quads.insert(quads.begin() + 2, bl_wall_back_horiz);
                    } else {
                        quads.insert(quads.begin() + 2, bl_wall_right_vert);
                    }
                }
                
                if(s && e) {
                    quads.insert(quads.begin() + 3, br_black);
                } else {
                    if(!s) {
                        quads.insert(quads.begin() + 3, br_wall_back_horiz);
                    } else {
                        quads.insert(quads.begin() + 3, br_wall_left_vert);
                    }
                }
            } else if(dungeon->getMid(x, y) == 2){
                // TODO doors
                quads.insert(quads.begin() + 0, tl_floor);
                quads.insert(quads.begin() + 1, tr_floor);
                quads.insert(quads.begin() + 2, bl_floor);
                quads.insert(quads.begin() + 3, br_floor);
                
//                quads.insert(quads.begin() + 0, tl_floor_dec_semi_in);
//                quads.insert(quads.begin() + 1, tr_floor_dec_semi_in);
//                quads.insert(quads.begin() + 2, bl_floor_dec_semi_in);
//                quads.insert(quads.begin() + 3, br_floor_dec_semi_in);
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

#include "Terrain.h"
#include "Tilemap.h"

Terrain::Terrain() {

    tiletex.loadFromFile("resources/tilemap.png");

    complex = new Tilemap(tiletex, quadSize, height, width);

    generateFromSeed(120); // TODO make sample menu dungeon
    // buildTilemaps();

}

void Terrain::generateFromSeed(int seed) {
    dungeon = new Dungeon(height, width, 6, 10, seed);
    dungeon->create();
    
    buildTilemaps();
    
//    complex->setPosition(0, 0);
//    complex->setOrigin(-height * 16 / 2, -512);
    std::cout << "Built tilemaps!" << std::endl;
}

void Terrain::buildTilemaps() {
    for (int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            std::vector<QuadType> quads;
            quads.reserve(4);
            
            TileType ttype = dungeon->getTile(x, y);
            physics[y][x] = ttype;
        
            if(ttype == wall) {
                // draw walls
                
                // TODO morgan's new code should fix
                
                // check around wall to see what's wall and what's not.
                bool n  = (y == 0   || dungeon->getTile(x, y - 1) == 1);
                bool e  = (x == 127 || dungeon->getTile(x + 1, y) == 1);
                bool s  = (y == 127 || dungeon->getTile(x, y + 1) == 1);
                bool w  = (x == 0   || dungeon->getTile(x - 1, y) == 1);
                
                bool ne = (y == 0   || x == 127 || dungeon->getTile(x + 1, y - 1) == 1);
                bool nw = (y == 0   || x == 0   || dungeon->getTile(x - 1, y - 1) == 1);
                bool se = (y == 127 || x == 127 || dungeon->getTile(x + 1, y + 1) == 1);
                bool sw = (y == 127 || x == 0   || dungeon->getTile(x - 1, y + 1) == 1);
                
                // Top Left
                if(!s) {
                    if(!w) {
                        quads.insert(quads.begin() + 0, tl_wall_back_vert);
                    } else {
                        quads.insert(quads.begin() + 0, tl_wall_back_horiz);
                    }
                } else {
                    if(!n) {
                        if(!w) {
                            quads.insert(quads.begin() + 0, tl_wall_bottom_down);
                        } else {
                            quads.insert(quads.begin() + 0, tl_wall_bottom_horiz);
                        }
                    } else {
                        if(!w) {
                            quads.insert(quads.begin() + 0, tl_wall_right_vert);
                        } else {
                            if(!sw) {
                                quads.insert(quads.begin() + 0, tl_wall_right_horiz);
                            } else if(!nw) {
                                quads.insert(quads.begin() + 0, tl_wall_bottom_up);
                            } else {
                                quads.insert(quads.begin() + 0, tl_black);
                            }
                        }
                    }
                }
                
                // Top Right
                if(!s) {
                    if(!e) {
                        quads.insert(quads.begin() + 1, tr_wall_back_vert);
                    } else {
                        quads.insert(quads.begin() + 1, tr_wall_back_horiz);
                    }
                } else {
                    if(!n) {
                        if(!e) {
                            quads.insert(quads.begin() + 1, tr_wall_bottom_down);
                        } else {
                            quads.insert(quads.begin() + 1, tr_wall_bottom_horiz);
                        }
                    } else {
                        if(!e) {
                            quads.insert(quads.begin() + 1, tr_wall_left_vert);
                        } else {
                            if(!se) {
                                quads.insert(quads.begin() + 1, tr_wall_left_horiz);
                            } else if(!ne) {
                                quads.insert(quads.begin() + 1, tr_wall_bottom_up);
                            } else {
                                quads.insert(quads.begin() + 1, tr_black);
                            }
                        }
                    }
                }
                
                // Bottom left
                if(!s) {
                    if(!w) {
                        quads.insert(quads.begin() + 2, bl_wall_back_vert);
                    } else {
                        quads.insert(quads.begin() + 2, bl_wall_back_horiz);
                    }
                } else {
                    if(!w || !sw) {
                        quads.insert(quads.begin() + 2, bl_wall_right_vert);
                    } else {
                        quads.insert(quads.begin() + 2, bl_black);
                    }
                }
            
                // Bottom right
                if(!s) {
                    if(!e) {
                        quads.insert(quads.begin() + 3, br_wall_back_vert);
                    } else {
                        quads.insert(quads.begin() + 3, br_wall_back_horiz);
                    }
                } else {
                    if(!e || !se) {
                        quads.insert(quads.begin() + 3, br_wall_left_vert);
                    } else {
                        quads.insert(quads.begin() + 3, br_black);
                    }
                }
                
            } else if(ttype == door){
                // TODO pass through doors
                physics[y][x] = ground;
                
                // TODO doors
                quads.insert(quads.begin() + 0, tl_floor);
                quads.insert(quads.begin() + 1, tr_floor);
                quads.insert(quads.begin() + 2, bl_floor);
                quads.insert(quads.begin() + 3, br_floor);
                
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
}

void Terrain::update(float elapsedTime) {
    // TODO
}

void Terrain::draw(float cameraX, float cameraY, sf::RenderWindow *app) {
    app->draw(*complex);
}

TileType Terrain::getTile(int tileX, int tileY, std::string layer) {
    return physics[tileY][tileX];
}

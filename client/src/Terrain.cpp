#include "Terrain.h"
#include "Tilemap.h"

Terrain::Terrain() {

    tiletex.loadFromFile("resources/tilemap.png");

    complex = new Tilemap(tiletex, quadSize, height, width);
    decoration = new Tilemap(tiletex, quadSize, height, width);
    
    std::vector<std::vector<TileType> > lobbyTiles(width);
    for(int i = 0; i < width; i++) {
        lobbyTiles[i] = std::vector<TileType>(height, wall);
    }
    
    for(int i = 62; i < 67; i++) {
        for(int j = 62; j < 67; j++) {
            lobbyTiles[i][j] = ground;
        }
    }
    
    buildTilemaps(lobbyTiles);
    
//    generateFromSeed(2454);
}

void Terrain::generateFromSeed(int seed) {
    dungeon = new Dungeon(height, width, 6, 10, seed);
    dungeon->create();
    
    buildTilemaps(dungeon->getTiles());
    
    std::cout << "Built tilemaps!" << std::endl;
}

void Terrain::buildTilemaps(std::vector<std::vector<TileType> > tileList) {
    for (int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            std::vector<QuadType> complexQuads(4, blank);
            std::vector<QuadType> decorationQuads(4, blank);
            
            TileType ttype = tileList[x][y];
            physics[x][y] = ttype;
        
            // check around wall to see what's wall and what's not.
            bool n  = (y == 0   || tileList[x][y - 1] == wall);
            bool e  = (x == 127 || tileList[x + 1][y] == wall);
            bool s  = (y == 127 || tileList[x][y + 1] == wall);
            bool w  = (x == 0   || tileList[x - 1][y] == wall);
            
            bool ne = (y == 0   || x == 127 || tileList[x + 1][y - 1] == wall);
            bool nw = (y == 0   || x == 0   || tileList[x - 1][y - 1] == wall);
            bool se = (y == 127 || x == 127 || tileList[x + 1][y + 1] == wall);
            bool sw = (y == 127 || x == 0   || tileList[x - 1][y + 1] == wall);
            
            if(ttype == wall) {
                physics[x][y] = wall;
                
                // Top Left
                if(!s) {
                    if(!w) {
                        complexQuads.insert(complexQuads.begin() + 0, tl_wall_back_vert);
                    } else {
                        complexQuads.insert(complexQuads.begin() + 0, tl_wall_back_horiz);
                    }
                } else {
                    if(!n) {
                        if(!w) {
                            complexQuads.insert(complexQuads.begin() + 0, tl_wall_bottom_down);
                        } else {
                            complexQuads.insert(complexQuads.begin() + 0, tl_wall_bottom_horiz);
                        }
                    } else {
                        if(!w) {
                            complexQuads.insert(complexQuads.begin() + 0, tl_wall_right_vert);
                        } else {
                            if(!sw) {
                                complexQuads.insert(complexQuads.begin() + 0, tl_wall_right_horiz);
                            } else if(!nw) {
                                complexQuads.insert(complexQuads.begin() + 0, tl_wall_bottom_up);
                            } else {
                                complexQuads.insert(complexQuads.begin() + 0, tl_black);
                            }
                        }
                    }
                }
                
                // Top Right
                if(!s) {
                    if(!e) {
                        complexQuads.insert(complexQuads.begin() + 1, tr_wall_back_vert);
                    } else {
                        complexQuads.insert(complexQuads.begin() + 1, tr_wall_back_horiz);
                    }
                } else {
                    if(!n) {
                        if(!e) {
                            complexQuads.insert(complexQuads.begin() + 1, tr_wall_bottom_down);
                        } else {
                            complexQuads.insert(complexQuads.begin() + 1, tr_wall_bottom_horiz);
                        }
                    } else {
                        if(!e) {
                            complexQuads.insert(complexQuads.begin() + 1, tr_wall_left_vert);
                        } else {
                            if(!se) {
                                complexQuads.insert(complexQuads.begin() + 1, tr_wall_left_horiz);
                            } else if(!ne) {
                                complexQuads.insert(complexQuads.begin() + 1, tr_wall_bottom_up);
                            } else {
                                complexQuads.insert(complexQuads.begin() + 1, tr_black);
                            }
                        }
                    }
                }
                
                // Bottom left
                if(!s) {
                    if(!w) {
                        complexQuads.insert(complexQuads.begin() + 2, bl_wall_back_vert);
                    } else {
                        complexQuads.insert(complexQuads.begin() + 2, bl_wall_back_horiz);
                    }
                } else {
                    if(!w || !sw) {
                        complexQuads.insert(complexQuads.begin() + 2, bl_wall_right_vert);
                    } else {
                        complexQuads.insert(complexQuads.begin() + 2, bl_black);
                    }
                }
            
                // Bottom right
                if(!s) {
                    if(!e) {
                        complexQuads.insert(complexQuads.begin() + 3, br_wall_back_vert);
                    } else {
                        complexQuads.insert(complexQuads.begin() + 3, br_wall_back_horiz);
                    }
                } else {
                    if(!e || !se) {
                        complexQuads.insert(complexQuads.begin() + 3, br_wall_left_vert);
                    } else {
                        complexQuads.insert(complexQuads.begin() + 3, br_black);
                    }
                }
//                
//            } else if(ttype == door){
//                // TODO pass through doors
//                physics[x][y] = ground;
//                
//                // TODO doors
//                complexQuads.insert(complexQuads.begin() + 0, tl_floor);
//                complexQuads.insert(complexQuads.begin() + 1, tr_floor);
//                complexQuads.insert(complexQuads.begin() + 2, bl_floor);
//                complexQuads.insert(complexQuads.begin() + 3, br_floor);
                
            } else {
                // TODO pass through doors
                physics[x][y] = ground;
                
                // Draw the floor
                complexQuads.insert(complexQuads.begin() + 0, tl_floor);
                complexQuads.insert(complexQuads.begin() + 1, tr_floor);
                complexQuads.insert(complexQuads.begin() + 2, bl_floor);
                complexQuads.insert(complexQuads.begin() + 3, br_floor);
                
                // Determine what floor ring to draw
                
                // Draw top left quad
                if(n) {
                    if(w) {
                        decorationQuads.insert(decorationQuads.begin() + 0, tl_floor_dec_semi_in);
                    } else {
                        decorationQuads.insert(decorationQuads.begin() + 0, tl_floor_dec_full_horiz);
                    }
                } else {
                    if(nw) {
                        if(w) {
                            decorationQuads.insert(decorationQuads.begin() + 0, tl_floor_dec_full_vert);
                        } else {
                            decorationQuads.insert(decorationQuads.begin() + 0, tl_floor_dec_semi_out);
                        }
                    }
                }
                
                // Draw top right quad
                if(n) {
                    if(e) {
                        decorationQuads.insert(decorationQuads.begin() + 1, tr_floor_dec_semi_in);
                    } else {
                        decorationQuads.insert(decorationQuads.begin() + 1, tr_floor_dec_full_horiz);
                    }
                } else {
                    if(ne) {
                        if(e) {
                            decorationQuads.insert(decorationQuads.begin() + 1, tr_floor_dec_full_vert);
                        } else {
                            decorationQuads.insert(decorationQuads.begin() + 1, tr_floor_dec_semi_out);
                        }
                    }
                }
                
                // Draw bottom left quad
                if(w) {
                    if(nw) {
                        if(s) {
                            decorationQuads.insert(decorationQuads.begin() + 2, bl_floor_dec_semi_in);
                        } else {
                            decorationQuads.insert(decorationQuads.begin() + 2, bl_floor_dec_full_vert);
                        }
                    } else {
                        decorationQuads.insert(decorationQuads.begin() + 2, bl_floor_dec_semi_out);
                    }
                }
                
                // Draw bottom right quad
                if(e) {
                    if(ne) {
                        if(s) {
                            decorationQuads.insert(decorationQuads.begin() + 3, br_floor_dec_semi_in);
                        } else {
                            decorationQuads.insert(decorationQuads.begin() + 3, br_floor_dec_full_vert);
                        }
                    } else {
                        decorationQuads.insert(decorationQuads.begin() + 3, br_floor_dec_semi_out);
                    }
                }
                
            }
            
            Tile complexTile = Tile(x, y, complexQuads);
            Tile decorationTile = Tile(x, y, decorationQuads);
            
            complex->setTile(complexTile);
            decoration->setTile(decorationTile);
        }
    }
}

void Terrain::update(float elapsedTime) {
    // TODO
}

void Terrain::draw(float cameraX, float cameraY, sf::RenderWindow *app) {
    app->draw(*complex);
    app->draw(*decoration);
}

TileType Terrain::getTile(int tileX, int tileY, std::string layer) {
    return physics[tileX][tileY];
}

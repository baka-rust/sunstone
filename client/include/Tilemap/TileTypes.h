#ifndef TILETYPES_H
#define TILETYPES_H

static const int TILES_PER_ROW = 32;

enum TileType {
    ground = 0 ,
    wall ,
    door ,
    healthpack ,
    spawner
};

#endif // TILETYPES_H

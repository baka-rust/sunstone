#ifndef TILETYPES_H
#define TILETYPES_H

static const int TILES_PER_ROW = 32;

enum TileType {
    ground,
    wall,
    door,
    healthpack,
    spawner
};

#endif // TILETYPES_H
#include <queue>
#include <map>

#include "PathMapper.h"
#include "Dungeon.h"

PathMapper::PathMapper(Dungeon* d) {
    dungeon = d;
    wallBitmap = dungeon->getWalls();
}

std::vector<int> PathMapper::getLocalPath(int ID, int x, int y) {
    std::vector<int> r(4);
    
    r[0] = pathMap[ID][x][y-1];
    r[1] = pathMap[ID][x+1][y];
    r[2] = pathMap[ID][x][y+1];
    r[3] = pathMap[ID][x-1][y];
    
    return r;
}

void PathMapper::createMap(int ID, int x, int y) {
    
    for(int i=0; i<dungeon->width(); i++) {
        pathMap[i].reserve(dungeon->width());
        for(int j=0; j<dungeon->height(); j++) {
            if(wallBitmap[i][j]) {
                pathMap[ID][i][j] = -1;
            }
            else {
                pathMap[ID][i][j] = -1;
            }
        }
    }

    
    // we process elements by twos, (x,y)
    std::queue<int> q;
    q.push(x);
    q.push(y);
    
    int currentX;
    int currentY;
    while(q.size()!=0) {
    }
}
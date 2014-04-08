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
    if(wallBitmap[x][y]) {
        return;
    }
    
    pathMap[ID].resize(dungeon->width());
    for(int x = 0; x< dungeon->width(); x++) {
        pathMap[ID][x].resize(dungeon->height());
        for(int y=0; y<dungeon->height(); y++) {
            if(wallBitmap[x][y]) {
                pathMap[ID][x][y] = 9000;
            }
            else {
                pathMap[ID][x][y] = -1;
            }
        }
    }

    
    // we process elements by twos, (x,y)
    std::queue<int> q;
    
    pathMap[ID][x][y] = 0;
    q.push(x);
    q.push(y);
    
    int currentX;
    int currentY;
    while(q.size() != 0) {
        currentX = q.front();
        q.pop();
        currentY = q.front();
        q.pop();
        if(currentX > 0) {
            if(pathMap[ID][currentX-1][currentY] < 0) {
                pathMap[ID][currentX-1][currentY] = pathMap[ID][currentX][currentY] + 1;
                q.push(currentX - 1);
                q.push(currentY);
            }
        }
        if(currentX < dungeon->width() - 1) {
            if(pathMap[ID][currentX + 1][currentY] < 0) {
                pathMap[ID][currentX + 1][currentY] = pathMap[ID][currentX][currentY] + 1;
                q.push(currentX+1);
                q.push(currentY);
            }
        }
        if(currentY > 0) {
            if(pathMap[ID][currentX][currentY - 1] < 0) {
                pathMap[ID][currentX][currentY - 1] = pathMap[ID][currentX][currentY] + 1;
                q.push(currentX);
                q.push(currentY-1);
            }
        }
        if(currentY < dungeon->height() - 1) {
            if(pathMap[ID][currentX][currentY + 1] < 0) {
                pathMap[ID][currentX][currentY + 1] = pathMap[ID][currentX][currentY] + 1;
                q.push(currentX);
                q.push(currentY + 1);
            }
        }
    }
}
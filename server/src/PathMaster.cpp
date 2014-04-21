#include <queue>
#include <map>

#include "PathMaster.h"
#include "Dungeon.h"

PathMaster::PathMaster(Dungeon* d) {
    dungeon = d;
    wallBitmap = dungeon->getWalls();
}

std::string PathMaster::getLocalPath(int ID, int fromX, int fromY, int toX, int toY) {
    
    int dx = fromX - toX;
    int dy = fromY - toY;
    
    if(abs(dx) > abs(dy)) { // prioritize minimizing dx distance if it is bigger than dy
        if(pathMap[ID][toX+1][toY] < pathMap[ID][toX][toY]) {
            return "right";
        }
        else if(pathMap[ID][toX-1][toY] < pathMap[ID][toX][toY]) {
            return "left";
        }
        else if(pathMap[ID][toX][toY] < pathMap[ID][toX][toY]) {
            return "down";
        }
        else {
            return "up";
        }
    }
    else { // prioritize minimizing dy distance if it is bigger than dx
        if(pathMap[ID][toX][toY+1] < pathMap[ID][toX][toY]) {
            return "down";
        }
        else if(pathMap[ID][toX][toY-1] < pathMap[ID][toX][toY]) {
            return "up";
        }
        else if(pathMap[ID][toX-1][toY] < pathMap[ID][toX][toY]) {
            return "left";
        }
        else {
            return "right";
        }
    }
}

void PathMaster::createMap(int ID, int x, int y) {
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
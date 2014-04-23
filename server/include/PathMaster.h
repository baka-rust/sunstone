#ifndef PATHMAPPER_H
#define PATHMAPPER_H

#include <map>
#include <vector>

#include "Dungeon.h"

class PathMaster {
    
    public:
    
        PathMaster(Dungeon* d);
    
        // overwrite pathMap[mapNumber] with distance mappings to (x,y)
        // in other words, to get to (x,y), call this function
        void createMap(int ID, int x, int y);
    
        // returns which tile to go to (0 = up; 1 = right; 2 = down; 3 = left)
        std::string getLocalPath(int ID, int fromX, int fromY, int toX, int toY);
    
    private:
    
        Dungeon* dungeon;

        // bitmap of whether a tile is a wall or not
        std::vector< std::vector<bool> > wallBitmap;
    
        // map of pathMaps to IDs
        std::map<int, std::vector< std::vector<int> > > pathMap;
};

#endif // PATHMAPPER_H

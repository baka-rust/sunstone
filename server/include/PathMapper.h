#ifndef PATHMAPPER_H
#define PATHMAPPER_H

#include <map>
#include <vector>

#include "Dungeon.h"

class PathMapper {
    
    public:
    
        PathMapper(Dungeon* d);
    
        // overwrite pathMap[mapNumber] with distance mappings to (x,y)
        void createMap(int ID, int x, int y);
    
        // returns values of the surrounding tiles (up, right, down, left)
        std::vector<int> getLocalPath(int ID, int x, int y);
    

    private:
    
        Dungeon* dungeon;
        std::vector< std::vector<bool> > wallBitmap;
        std::map<int, std::vector< std::vector<int> > > pathMap;
};

#endif // PATHMAPPER_H

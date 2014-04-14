#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <stdlib.h>

#include "Room.h"
#include "TileTypes.h"

/*
 0 = empty
 1 = wall
 2 = door
 */

class Dungeon {
    
public:
    
    Dungeon(int width, int height, int minRoomSize, int maxRoomSize, int seed);
    void create();
    
    // what room is (x,y) in?  returns -1 if not in any rooms
    int getRoom(int x, int y);
    
    // get bitmap of whether tile[i]==value
    std::vector< std::vector<bool> > getBitmap(int value);
    
    // get a bitmap of features
    std::vector< std::vector<bool> > getWalls();
    std::vector< std::vector<bool> > getFloors();
    
    // returns a 2D int-grid of distances from (x,y) in the room (x,y) is in
    std::vector< std::vector<int> > getPathMap(int x, int y);
    
    // accessors
    int width() { return (int) grid.size(); };
    int height() { return (int) grid[0].size(); };
    TileType getTile(int x, int y);
    bool isFloor(int x, int y);
    bool isWall(int x, int y);
    std::vector< std::vector<TileType> > getTiles();
    
    
private:
    
    std::vector< std::vector<TileType> > grid;
    std::vector<Room> rooms;
    std::vector<Door> doors;
    
    int roomCount;
    int minRoomSize;
    int maxRoomSize;
    
    // used as seed for next random number
    int lastRandomNumber;
    
    
    // dungeon creation methods
    int createAttempt();
    bool addBranch(Room r);
    void carveSquare(int x, int y, int width, int height, TileType value);
    bool checkSquare(int x, int y, int width, int height, TileType value);
    void decorateRoom(Room room);
    
    // random numbers
    int getRandomNumber();
    int randInt(int min, int max);
    
    // printing (for debugging)
    void printLine(int y);
    void printGrid();
    
};

#endif // DUNGEON_H

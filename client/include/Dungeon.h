#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <stdlib.h>

#include "Room.h"

/*
 0 = empty
 1 = wall
 2 = door
 */

class Dungeon {

    public:

        Dungeon(int width, int height, int minRoomSize, int maxRoomSize, int seed);
        void create();
        int getTile(int x, int y);
        bool getFloor(int x, int y);
        bool getWall(int x, int y);
        int getRoom(int x, int y);
        std::vector< std::vector<bool> > getBitmap(int value);
        std::vector< std::vector<bool> > getWalls();
        std::vector< std::vector<bool> > getFloors();
        std::vector< std::vector<int> > getPathMap(int x, int y);
        int width(){return (int)grid.size();};
        int height(){return (int)grid[0].size();};

    private:

        std::vector< std::vector<int> > grid;
        std::vector<Room> rooms;
        std::vector<Door> doors;
        int roomsLength;
        int minRoomSize;
        int maxRoomSize;
        int lastRandomNumber;

        int createAttempt();
        void carveSquare(int x, int y, int width, int height, int value);
        bool checkSquare(int x, int y, int width, int height, int value);
        int getRandomNumber();
        void decorateRoom(Room room);
        int randInt(int min, int max);
        bool addBranch(Room r);
        void printLine(int y);
        void printGrid();
    
};

#endif // DUNGEON_H

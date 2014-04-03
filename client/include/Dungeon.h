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
        int getMid(int x, int y);
        bool getFloor(int x, int y);
        bool getWall(int x, int y);
        std::vector< std::vector<bool> > getBitmap(int value);
        std::vector< std::vector<bool> > getWalls();
        std::vector< std::vector<bool> > getFloors();
    
    private:

        std::vector< std::vector<int> > grid;
        std::vector<Room> rooms;
        std::vector<Door> doors;
        int roomsLength;
        int minRoomSize;
        int maxRoomSize;
        int lastRandomNumber;

    
        void carveSquare(int x, int y, int width, int height, int value);
        bool checkSquare(int x, int y, int width, int height, int value);
        int getRandomNumber();
        int randInt(int min, int max);
        bool addBranch(Room r);
        void printLine(int y);
        void printGrid();

};

#endif // DUNGEON_H

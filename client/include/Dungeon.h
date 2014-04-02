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

    private:

        std::vector< std::vector<int> > grid;
        std::vector<Room> rooms;
        std::vector<Door> doors;
        int roomsLength;
        void carveSquare(int x, int y, int width, int height, int value);
        bool checkSquare(int x, int y, int width, int height, int value);
        bool addBranch(Room r);
        void printLine(int y);
        void printGrid();
        int randInt(int min, int max);
        int minRoomSize;
        int maxRoomSize;
        int lastRandomNumber;
        int getRandomNumber();

};

#endif // DUNGEON_H

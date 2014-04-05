#include "Room.h"
#include <iostream>

Room::Room(int x, int y, int width, int height) {
    _x = x;
    _y = y;
    _width = width;
    _height = height;
    _endX = _x + _width;
    _endY = _y + _height;
}

void Room::addConnectedRoom(Room room, Door d) {
    _connectedRooms[_numberOfConnectedRooms] = &room;
    _doors[_numberOfConnectedRooms] = d;
    _numberOfConnectedRooms++;
}

bool Room::inRoom(int x, int y) {
    return x >= _x
    && x < _endX
    && y >= _y
    && y < _endY;
}
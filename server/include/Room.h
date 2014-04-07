#ifndef ROOM_H
#define ROOM_H

struct Door {
    int x;
    int y;
};

class Room {

    public:

        Room(int x, int y, int width, int height);
        int x() { return _x; };
        int y() { return _y; };
        int height() { return _height; };
        int width() { return _width; };
        int endX() { return _endX; };
        int endY() { return _endY; };
        void addConnectedRoom(Room room, Door door);
        bool inRoom(int x, int y);

    private:

        int _x;
        int _y;
        int _width;
        int _height;
        int _endX;
        int _endY;
        int _numberOfConnectedRooms = 0;
        Room* _connectedRooms[4];
        Door _doors[4];

};

#endif // ROOM_H

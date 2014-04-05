#include "Dungeon.h"
#include <queue>

Dungeon::Dungeon(int width, int height, int minRoom, int maxRoom, int seed) {
    minRoomSize = minRoom;
    maxRoomSize = maxRoom;

    lastRandomNumber = seed;

    rooms.reserve(128);
    doors.reserve(128);
    roomsLength = 0;

    grid = std::vector< std::vector<int> >(width);
    for(int i=0; i<width; i++) {
        grid[i] = std::vector<int> (height);
    }
}

int Dungeon::getRandomNumber() {
    lastRandomNumber = abs(130021*lastRandomNumber+94291)%1543;
    return lastRandomNumber;
}

int Dungeon::randInt(int min, int max) {
    return min + getRandomNumber() % (max - min);
}

void Dungeon::create() {
    for(int x=0; x<grid.size(); x++) {   // set grid to all walls
        for(int y=0; y<grid[0].size(); y++) {
            grid[x][y] = 1;
        }
    }
    
    carveSquare((int)grid.size()/2, (int)grid[0].size()/2, 8, 8, 0);       // carve original room
    rooms[0] = Room((int)grid.size()/2, (int)grid[0].size()/2, 8, 8);         // and add it to list of rooms
    roomsLength++;

    for(int i=0; i<10; i++) {            // add 10 rooms along a single path (this is the main path)
        int j = 0;
        while(!addBranch(rooms[i])) {
            j += 1;
            if(j > 100) {
                break;
            }
        } 
    }

    int finalRoom = roomsLength - 1;

    for(int branch=0; branch<3; branch++){
        for(int i=0; i<10+branch*5; i++) {            // add a branch off of each room on the main path
            int j = 0;
            while(!addBranch(rooms[i])) {
                j += 1;
                if(j > 100) {
                    break;
                }
            }
        }
    }

    carveSquare((int)grid.size()/2, (int)grid[0].size()/2, 8, 8, 3);       // overwrite the starting and final rooms with "3"
    carveSquare(rooms[finalRoom].x(), rooms[finalRoom].y(), rooms[finalRoom].width(), rooms[finalRoom].height(), 3);
}

int Dungeon::getMid(int x, int y) {
    return grid[x][y];
}

bool Dungeon::getFloor(int x, int y) {
    return grid[x][y] == 0;
}

bool Dungeon::getWall(int x, int y) {
    return grid[x][y] == 1;
}

int Dungeon::getRoom(int x, int y){
    int i;
    for(i=0; i<rooms.size(); i++){
        if(rooms[i].inRoom(x, y)){
            return i;
        }
    }
    std::cout << "nope, not in a room";
    return -1;
}

std::vector< std::vector<int> > Dungeon::getPathMap(int x, int y){
    int rm = getRoom(x,y);
    if(rm == -1){
        throw "Error!  Trying to pathfind outside of the dungeon";
        return std::vector< std::vector<int> > (0);
    }
    Room room = rooms[rm];
    std::vector< std::vector<int> > r(room.width()+2);
    r[0] = std::vector<int>(room.height()+2);
    for(int i=0; i<r[0].size(); i++){
        r[0][i] = 999; // wall;
    }
    for(int i=1; i<r.size()-1; i++){
        r[i] = std::vector<int>(room.height()+2);
        r[i][0] = 999; // wall
        r[i][r[0].size()-1] = 999; // wall
        for(int j=1; j<r[0].size()-1; j++){
            r[i][j] = -1;
        }
    }
    r[r.size()-1] = std::vector<int>(room.height()+2);
    for(int i=0; i<r[r.size()-1].size(); i++){
        r[0][i] = 999; // wall;
    }
    
    // TODO: add doors HERE
    
    std::queue<int> queue;
    queue.push(x);
    queue.push(y);

    int nx;
    int ny;
    while(queue.size() != 0){
        nx = queue.front();
        queue.pop();
        ny = queue.front();
        queue.pop();
        if(nx>0 && r[nx-1][ny]==-1){
            r[nx-1][ny] = r[nx][ny]+1;
            queue.push(nx-1);
            queue.push(ny);
        }
        if(nx<room.width()-1 && r[nx+1][ny]==-1){
            r[nx-1][ny] = r[nx][ny]+1;
            queue.push(nx+1);
            queue.push(ny);
        }
        if(ny>0 && r[nx][ny-1]==-1){
            r[nx][ny-1] = r[nx][ny]+1;
            queue.push(nx);
            queue.push(ny-1);
        }
        if(ny>room.height()-1 && r[nx][ny+1]==-1){
            r[nx][ny+1] = r[nx][ny]+1;
            queue.push(nx);
            queue.push(ny+1);
        }
    }
    return r;
}

std::vector< std::vector<bool> > Dungeon::getBitmap(int value) {
    std::vector< std::vector<bool> > r = std::vector< std::vector<bool> >(grid.size());
    for(int i=0; i<r.size(); i++){
        r[i] = std::vector<bool>(grid[0].size());
    }
    for(int x=0; x<grid.size(); x++) {
        for(int y=0; y<grid[0].size(); y++) {
            r[x][y] = grid[x][y] == value;
        }
    }
    return r;
}

std::vector< std::vector<bool> > Dungeon::getWalls() {
    return getBitmap(1);
}

std::vector< std::vector<bool> > Dungeon::getFloors() {
    return getBitmap(0);
}

bool Dungeon::checkSquare(int x, int y, int width, int height, int value) {
    // check to see if a rectangle contains only a given value
    for(int _x = x; _x < x + width; _x++) {
        if(_x >= grid.size()) {
            return false;
        }
        
        for(int _y = y; _y < y + height; _y++) {
            if(_y >= grid[0].size()) {
                return false;
            }
            
            if(grid[_x][_y] != value) {
                return false;
            }
        }
    }
    return true;
}

void Dungeon::carveSquare(int x, int y, int width, int height, int value) {
    // set a rectangle to a given value
	for(int _y=y; _y<y+height; _y++) {
		if(_y>=grid[0].size()) {
            break;
		}
		for(int _x=x; _x<x+width; _x++) {
			if(_x>=grid.size()) {
				break;
			}
            grid[_x][_y] = value;
		}
	}
}

bool Dungeon::addBranch(Room room) { // try to add a random room to the input
    int width = minRoomSize + getRandomNumber() % (maxRoomSize - minRoomSize);
    int height = minRoomSize + getRandomNumber() % (maxRoomSize - minRoomSize);
    if(getRandomNumber()%256 > 127) {
        if(getRandomNumber()%256>127) {
            // create square above 'room'
            int x = randInt(room.x() - width + 3, room.x() + room.width() - 2); // room placement
            if(!checkSquare(x - 2, room.y() - height - 4, width + 4, height + 4, 1)) {
                return false;
            }
            int n = randInt(x, x + width - 1);  // door placement
            while(n < room.x() || n + 1 >= room.endX()) {
				n = randInt(x,x+width-1);
            }

            carveSquare(x, room.y() - height - 2, width, height, 0);    // carve both
			carveSquare(n, room.y() - 2, 2, 2, 2);

            doors[roomsLength-1].x = n;
            doors[roomsLength-1].y = room.y() - 2;

            rooms[roomsLength] = Room(x, room.y() - height - 2, width, height);
            rooms[roomsLength].addConnectedRoom(room, doors[roomsLength-1]);
            room.addConnectedRoom(rooms[roomsLength], doors[roomsLength-1]);

            roomsLength++;
            return true;
        }
        else {
            // create square to the right of 'room'
            int y = randInt(room.y() - height + 3, room.y() + room.height() - 2); // room placement
            if(!checkSquare(room.x() + room.width(), y - 2, width + 4, height + 4, 1)) {
                return false;
            }
            int n = randInt(y, y + height - 1); // door placement
            while(n < room.y() || n + 1 >= room.endY()) {
                n = randInt(y, y + height - 1);
            }

            carveSquare(room.x() + room.width() + 2, y, width, height, 0);  // carve both
            carveSquare(room.x() + room.width(), n, 2, 2, 2);

            doors[roomsLength-1].x = room.x() + room.width();
            doors[roomsLength-1].y = n;

            rooms[roomsLength] = Room(room.x() + room.width() + 2, y, width, height);
            rooms[roomsLength].addConnectedRoom(room, doors[roomsLength-1]);
            room.addConnectedRoom(rooms[roomsLength], doors[roomsLength-1]);

            roomsLength++;
            return true;
        }
    }
    else {
        if(getRandomNumber()%256>127) {
            // create square beneath 'room'
            int x = randInt(room.x() - width + 3, room.x() + room.width() - 2); // room placement
            if(!checkSquare(x - 2, room.y() + room.height(), width + 4, height + 4, 1)) {
                return false;
            }
            int n = randInt(x, x + width - 1);  // door placement
            while(n < room.x() || n + 1 >= room.endX()) {
                n = randInt(x, x + width - 1);
            }
            carveSquare(x, room.y() + room.height() + 2, width, height, 0); // carve both
            carveSquare(n, room.y() + room.height(), 2, 2, 2);

            doors[roomsLength-1].x = n;
            doors[roomsLength-1].y = room.y() + room.height();

            rooms[roomsLength] = Room(x, room.y() + room.height() + 2, width, height);
            rooms[roomsLength].addConnectedRoom(room, doors[roomsLength-1]);
            room.addConnectedRoom(rooms[roomsLength], doors[roomsLength-1]);

            roomsLength++;
            return true;
        }
        else {
            // create square to the left of 'room'
            int y = randInt(room.y() - height + 3, room.y() + room.height() - 2);   // room placement
            if(!checkSquare(room.x() - width - 4, y - 2, width + 4, height + 4, 1)) {
                return false;
            }
            int n = randInt(y, y + height - 1); // door placement
            while(n < room.y() || n + 1 >= room.endY()) {
                n = randInt(y, y + height - 1);
            }
            carveSquare(room.x() - width - 2, y, width, height, 0); // carve both
            carveSquare(room.x() - 2, n, 2, 2, 2);

            doors[roomsLength-1].x = room.x() - 2;
            doors[roomsLength-1].y = n;

            rooms[roomsLength] = Room(room.x() - width - 2, y, width, height);
            rooms[roomsLength].addConnectedRoom(room, doors[roomsLength-1]);
            room.addConnectedRoom(rooms[roomsLength], doors[roomsLength-1]);

            roomsLength++;
            return true;
        }
    }
    return false;
}

void printDoubleIntVector(std::vector< std::vector<int> >r){
    for(int i=0; i<r[0].size(); i++){
        for(int j=0; j<r.size(); j++){
            std::cout << r[j][i];
        }
        std::cout << "\n";
    }
}

void Dungeon::printLine(int y) {
    for(int i=0; i<grid.size(); i++) {
        if(grid[i][y]==0) {
            std::cout << " ";
        }
        else if(grid[i][y]==1) {
            std::cout << "X";
        }
        else if(grid[i][y]==2) {
            std::cout << "[]";
            i++;
        }
        else {
            std::cout << "O";
        }
    }
}

void Dungeon::printGrid() {
    for(int i=0; i<grid[0].size(); i++) {
        printLine(i);
        std::cout << std::endl;
    }
}
#include "Dungeon.h"

#include <queue>

#include "Tilemap/TileTypes.h"

Dungeon::Dungeon(int width, int height, int minRoom, int maxRoom, int seed) {
    minRoomSize = minRoom;
    maxRoomSize = maxRoom;

    lastRandomNumber = seed;

    rooms.reserve(128);
    doors.reserve(128);
    roomCount = 0;

    grid = std::vector< std::vector<TileType> >(width);
    for(int i = 0; i < width; i++) {
        grid[i] = std::vector<TileType>(height);
    }
}

int Dungeon::getRandomNumber() {
    lastRandomNumber = abs( 130021 * lastRandomNumber + 94291 ) % 1543;
    return lastRandomNumber;
}

int Dungeon::randInt(int min, int max) {
    return min + getRandomNumber() % (max - min);
}

void Dungeon::create(){
    int n = 0;
    while(n < 3){
        lastRandomNumber++;
        n = createAttempt();
    }
    printGrid();
}

int Dungeon::createAttempt() {
    for(int x = 0; x < grid.size(); x++) {   // set grid to all walls
        for(int y = 0; y < grid[0].size(); y++) {
            grid[x][y] = wall;
        }
    }
    
    roomCount = 0;
    carveSquare((int) grid.size() / 2, (int) grid[0].size() / 2, 8, 8, ground);       // carve original room
    rooms[0] = Room((int) grid.size() / 2, (int) grid[0].size() / 2, 8, 8);         // and add it to list of rooms
    roomCount++;

    for(int i = 0; i < 10; i++) {            // add 10 rooms along a single path (this is the main path)
        int j = 0;
        while(!addBranch(rooms[i])) {
            j += 1;
            if(j > 100) {
                break;
            }
        } 
    }
    int finalRoom = roomCount - 1;

    for(int branch = 0; branch < 3; branch++){
        for(int i = 0; i < 10 + branch * 5; i++) {            // add a branch off of each room on the main path
            int j = 0;
            while(!addBranch(rooms[i])) {
                j += 1;
                if(j > 100) {
                    break;
                }
            }
        }
    }
    
    for(int i = 0; i < roomCount; i++){
//        decorateRoom(rooms[i]);
    }
    
    carveSquare((int) grid.size() / 2, (int)grid[0].size() / 2, 8, 8, ground);       // overwrite the starting and final rooms
    carveSquare(rooms[finalRoom].x(), rooms[finalRoom].y(), rooms[finalRoom].width(), rooms[finalRoom].height(), ground);
    
    return roomCount;
}

TileType Dungeon::getTile(int x, int y) {
    return grid[x][y];
}

bool Dungeon::isFloor(int x, int y) {
    return grid[x][y] == 0;
}

bool Dungeon::isWall(int x, int y) {
    return grid[x][y] == 1;
}

int Dungeon::getRoom(int x, int y) {
    int i;
    for(i = 0; i < roomCount; i++) {
        if(rooms[i].inRoom(x, y)) {
            return i;
        }
    }
    return -1;
}

std::vector< std::vector<int> > Dungeon::getPathMap(int x, int y) {
    int rm = getRoom(x, y);
    if(rm == -1) {
        throw "Error!  Trying to pathfind outside of the dungeon";
        return std::vector< std::vector<int> >(0);
    }
    Room room = rooms[rm];
    
    int width = room.width() + 2;
    int height = room.height() + 2;
    std::vector< std::vector<int> > r(width);

    for(int i = 0; i < width - 1; i++) {
        r[i] = std::vector<int>(height);
        for(int j = 0; j < width; j++) {
            r[i][j] = -1;
        }
    }
    
    // TODO: add doors HERE
    
    std::queue<int> queue;
    r[x - room.x()][y - room.y()] = 0;
    queue.push(x - room.x());
    queue.push(y - room.y());

    int item_x;
    int item_y;
    while(queue.size() != 0) {
        item_x = queue.front();
        queue.pop();
        item_y = queue.front();
        queue.pop();
        if(item_x > 0) {
            if(r[item_x-1][item_y] == -1) {
                r[item_x-1][item_y] = r[item_x][item_y] + 1;
                queue.push(item_x - 1);
                queue.push(item_y);
            }
        }
        if(item_x<room.width() - 1) {
            if(r[item_x + 1][item_y] == -1) {
                r[item_x + 1][item_y] = r[item_x][item_y] + 1;
                queue.push(item_x + 1);
                queue.push(item_y);
            }
        }
        if(item_y>  0) {
            if(r[item_x][item_y - 1] == -1) {
                r[item_x][item_y - 1] = r[item_x][item_y]+1;
                queue.push(item_x);
                queue.push(item_y - 1);
            }
        }
        if(item_y < room.height() - 1) {
            if(r[item_x][item_y + 1] == -1) {
                r[item_x][item_y + 1] = r[item_x][item_y] + 1;
                queue.push(item_x);
                queue.push(item_y + 1);
            }
        }
    }
    return r;
}

std::vector< std::vector<bool> > Dungeon::getBitmap(int value) {
    std::vector< std::vector<bool> > r = std::vector< std::vector<bool> >(grid.size());
    for(int i = 0; i < r.size(); i++) {
        r[i] = std::vector<bool>(grid[0].size());
    }
    
    for(int x = 0; x < grid.size(); x++) {
        for(int y = 0; y < grid[0].size(); y++) {
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

bool Dungeon::checkSquare(int x, int y, int width, int height, TileType value) {
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

void Dungeon::carveSquare(int x, int y, int width, int height, TileType value) {
    // set a rectangle to a given value
	for(int _y = y; _y < y+height; _y++) {
		if(_y>=grid[0].size()) {
            break;
		}
		for(int _x = x; _x < x+width; _x++) {
			if(_x >= grid.size()) {
				break;
			}
            grid[_x][_y] = value;
		}
	}
}

void Dungeon::decorateRoom(Room room) {
    int x;
    int y;
    if(randInt(0,3) == 0) {
        x = randInt(room.x() + 1, room.endX() - 1);
        y = randInt(room.y() + 1, room.endY() - 1);
        grid[x][y] = healthpack; // TODO somethignrater
    }
    
    int j = 0;
    int n = randInt(0,room.width()*room.height()/6);
    x = randInt(room.x()+1, room.endX()-1);
    y = randInt(room.y()+1, room.endY()-1);
    for(int i = 0; i < n; i++) {
        while(grid[x][y] != 0) {
            j++;
            x = randInt(room.x() + 1, room.endX() - 1);
            y = randInt(room.y() + 1, room.endY() - 1);
            if(j > 256) {
                return;
            }
        }
        grid[x][y] = wall;
    }
    
    n = randInt(3, 6);
    x = randInt(room.x()+1, room.endX()-1);
    y = randInt(room.y()+1, room.endY()-1);
    j = 0;
    for(int i = 0; i < n; i++) {
        while(grid[x][y] != 0) {
            j++;
            x = randInt(room.x()+1, room.endX()-1);
            y = randInt(room.y()+1, room.endY()-1);
            if(j > 100) {
                return;
            }
        }
        grid[x][y] = spawner;
    }

}

bool Dungeon::addBranch(Room room) { // try to add a random room to the input
    int width = minRoomSize + getRandomNumber() % (maxRoomSize - minRoomSize);
    int height = minRoomSize + getRandomNumber() % (maxRoomSize - minRoomSize);
    int j = 0;
    if(getRandomNumber()%256 > 127) {
        if(getRandomNumber()%256>127) {
            // create square above 'room'
            int x = randInt(room.x() - width + 3, room.x() + room.width() - 2); // room placement
            if(!checkSquare(x - 2, room.y() - height - 4, width + 4, height + 4, wall)) {
                return false;
            }
            
            int n = randInt(x, x + width - 1);  // door placement
            while(n < room.x() || n + 1 >= room.endX()) {
                j++;
				n = randInt(x, x + width - 1);
                if(j > 256){
                    return false;
                }
            }

            carveSquare(x, room.y() - height - 2, width, height, ground);    // carve both
			carveSquare(n, room.y() - 2, 2, 2, door);

            doors[roomCount-1].x = n;
            doors[roomCount-1].y = room.y() - 2;

            rooms[roomCount] = Room(x, room.y() - height - 2, width, height);
            rooms[roomCount].addConnectedRoom(room, doors[roomCount-1]);
            room.addConnectedRoom(rooms[roomCount], doors[roomCount-1]);

            roomCount++;
            return true;
        }
        else {
            // create square to the right of 'room'
            int y = randInt(room.y() - height + 3, room.y() + room.height() - 2); // room placement
            if(!checkSquare(room.x() + room.width(), y - 2, width + 4, height + 4, wall)) {
                return false;
            }
            
            int n = randInt(y, y + height - 1); // door placement
            while(n < room.y() || n + 1 >= room.endY()) {
                n = randInt(y, y + height - 1);
            }

            carveSquare(room.x() + room.width() + 2, y, width, height, ground);  // carve both
            carveSquare(room.x() + room.width(), n, 2, 2, ground);

            doors[roomCount-1].x = room.x() + room.width();
            doors[roomCount-1].y = n;

            rooms[roomCount] = Room(room.x() + room.width() + 2, y, width, height);
            rooms[roomCount].addConnectedRoom(room, doors[roomCount-1]);
            room.addConnectedRoom(rooms[roomCount], doors[roomCount-1]);

            roomCount++;
            return true;
        }
    }
    else {
        if(getRandomNumber() % 256 > 127) {
            // create square beneath 'room'
            int x = randInt(room.x() - width + 3, room.x() + room.width() - 2); // room placement
            if(!checkSquare(x - 2, room.y() + room.height(), width + 4, height + 4, wall)) {
                return false;
            }
            
            int n = randInt(x, x + width - 1);  // door placement
            while(n < room.x() || n + 1 >= room.endX()) {
                n = randInt(x, x + width - 1);
            }
            carveSquare(x, room.y() + room.height() + 2, width, height, ground); // carve both
            carveSquare(n, room.y() + room.height(), 2, 2, door);

            doors[roomCount-1].x = n;
            doors[roomCount-1].y = room.y() + room.height();

            rooms[roomCount] = Room(x, room.y() + room.height() + 2, width, height);
            rooms[roomCount].addConnectedRoom(room, doors[roomCount-1]);
            room.addConnectedRoom(rooms[roomCount], doors[roomCount-1]);

            roomCount++;
            return true;
        }
        else {
            // create square to the left of 'room'
            int y = randInt(room.y() - height + 3, room.y() + room.height() - 2);   // room placement
            if(!checkSquare(room.x() - width - 4, y - 2, width + 4, height + 4, wall)) {
                return false;
            }
            
            int n = randInt(y, y + height - 1); // door placement
            while(n < room.y() || n + 1 >= room.endY()) {
                n = randInt(y, y + height - 1);
            }
            carveSquare(room.x() - width - 2, y, width, height, ground); // carve both
            carveSquare(room.x() - 2, n, 2, 2, door);

            doors[roomCount-1].x = room.x() - 2;
            doors[roomCount-1].y = n;

            rooms[roomCount] = Room(room.x() - width - 2, y, width, height);
            rooms[roomCount].addConnectedRoom(room, doors[roomCount-1]);
            room.addConnectedRoom(rooms[roomCount], doors[roomCount-1]);

            roomCount++;
            return true;
        }
    }
    return false;
}

void printDoubleIntVector(std::vector< std::vector<int> >r) {
    for(int i = 0; i < r[0].size(); i++) {
        for(int j = 0; j < r.size(); j++) {
            std::cout << r[j][i];
        }
        std::cout << "\n";
    }
}

void Dungeon::printLine(int y) {
    for(int i = 0; i < grid.size(); i++) {
        if(grid[i][y] == ground) {
            std::cout << " ";
        }
        else if(grid[i][y] == wall) {
            std::cout << "X";
        }
        else if(grid[i][y] == door) {
            std::cout << "[]";
            i++;
        }
        else if(grid[i][y] == healthpack) {
            std::cout << "+";
        }
        else if(grid[i][y] == spawner) {
            std::cout << "^";
        }
        else {
            std::cout << "O";
        }
    }
}

void Dungeon::printGrid() {
    for(int i = 0; i < grid[0].size(); i++) {
        printLine(i);
        std::cout << std::endl;
    }
}
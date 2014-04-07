#ifndef NETWORKEDMONSTER_H
#define NETWORKEDMONSTER_H

#include <string>

class NetworkedMonster {

	public:
	
		static int currentId = 0;
		
		int id;
		int x, y;
		std::string direction;
		
		NetworkedMonster(int x, int y, std::string direction);

};

#endif // NETWORKEDMONSTER_H
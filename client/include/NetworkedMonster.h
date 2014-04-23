#ifndef NETWORKEDMONSTER_H
#define NETWORKEDMONSTER_H

#include <string>
#include <vector>
#include <map>

#include "AnimationSequence.h"
#include "Terrain.h"

class NetworkedMonster {

	public:
		
		float x, y;
		int tileX, tileY;
		int speed = 40;
		std::string direction;
		bool onTile = true;
		
		NetworkedMonster(int xPos, int yPos, std::string dir, int type);
		void update(float elapsedTime);
		void draw(sf::RenderWindow *app);
		
	private:

        	std::map<std::string, AnimationSequence*> animations;
        	typedef std::map<std::string, AnimationSequence*>::iterator i_animations;

};

#endif // NETWORKEDMONSTER_H

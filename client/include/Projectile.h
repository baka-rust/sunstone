#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>
#include <map>
#include <iostream>

class Projectile {

	public:
		
		float x, y;
		int tileX, tileY;
		int speed = 100;
		std::string direction;
		float updateTime;
		bool onTile = true;
		
		Projectile(int xPos, int yPos, std::string dir);
		void update(float elapsedTime);
		void draw(sf::RenderWindow *app);
	
	private:

		sf::Texture textureLeft, textureRight, textureUp, textureDown;
		sf::Sprite spriteLeft, spriteRight, spriteUp, spriteDown;

};

#endif // PROJECTILE_H

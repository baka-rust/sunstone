#include "Projectile.h"

#include <SFML/Graphics.hpp>

Projectile::Projectile(int xPos, int yPos, std::string dir) {

	tileX = xPos / 16;
	tileY = yPos / 16;
	
	x = xPos;
	y = yPos;
	
	direction = dir;
	
	textureLeft.loadFromFile("resources/projectiles/projectile.png");
	textureRight.loadFromFile("resources/projectiles/projectile.png");
	textureUp.loadFromFile("resources/projectiles/projectile.png");
	textureDown.loadFromFile("resources/projectiles/projectile.png");
	textureLeft.setSmooth(false);
	textureRight.setSmooth(false);
	textureUp.setSmooth(false);
	textureDown.setSmooth(false);
	
	spriteLeft.setTexture(textureLeft);
	spriteRight.setTexture(textureRight);
	spriteUp.setTexture(textureUp);
	spriteDown.setTexture(textureDown);
	
	updateTime = 0;
	
}

void Projectile::update(float elapsedTime) {

	if(direction == "up")
		y = y - (speed * elapsedTime);
	else if(direction == "down")
		y = y + (speed * elapsedTime);
	else if(direction == "left")
		x = x - (speed * elapsedTime);
	else if(direction == "right")
		x = x + (speed * elapsedTime);
    
    spriteUp.setPosition(x, y);
    spriteDown.setPosition(x, y);
    spriteLeft.setPosition(x, y);
    spriteRight.setPosition(x, y);

}

void Projectile::draw(sf::RenderWindow *app) {

	if(direction == "up")
		app->draw(spriteUp);
	else if(direction == "down")
		app->draw(spriteDown);
	else if(direction == "left")
		app->draw(spriteLeft);
	else if(direction == "right")
		app->draw(spriteRight);

}

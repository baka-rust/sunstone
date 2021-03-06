#include "NetworkedMonster.h"

#include <iostream>

NetworkedMonster::NetworkedMonster(int xPos, int yPos, std::string dir, int type) {

	tileX = xPos;
	tileY = yPos;
	
	x = tileX * 16;
	y = tileY * 16;
	
	direction = dir;
	
    std::string walkResource = "resources/blob/walk";
    int walkFrames = 8;
    float walkSpeed = 0.02;

    animations["up"] = new AnimationSequence(walkResource, walkFrames, walkSpeed);
    animations["down"] = new AnimationSequence(walkResource, walkFrames, walkSpeed);
    animations["left"] = new AnimationSequence(walkResource, walkFrames, walkSpeed);
    animations["right"] = new AnimationSequence(walkResource, walkFrames, walkSpeed);

}

void NetworkedMonster::update(float elapsedTime) {

	bool moving = false;
	
    if(direction == "up") {
        if(y <= (tileY * 16)) {
            onTile = true;
        }
        else {
            onTile = false;
            moving = true;
            y = y - (speed * elapsedTime);
            animations["up"]->update(elapsedTime);
        }
    }
    else if(direction == "down") {
        if(y >= (tileY * 16)) {
            onTile = true;
        }
        else {
            onTile = false;
            moving = true;
            y = y + (speed * elapsedTime);
            animations["down"]->update(elapsedTime);
        }
    }
    else if(direction == "left") {
        if(x <= (tileX * 16)) {
            onTile = true;
        }
        else {
            onTile = false;
            moving = true;
            x = x - (speed * elapsedTime);
            animations["left"]->update(elapsedTime);
        }
    }
    else if(direction == "right") {
        if(x >= (tileX * 16)) {
            onTile = true;
        }
        else {
            onTile = false;
            moving = true;
            x = x + (speed * elapsedTime);
            animations["right"]->update(elapsedTime);
        }
    }

    if(!moving && onTile) {
        x = tileX * 16;
        y = tileY * 16;
    }

    // set animation positions
    for(i_animations iterator = animations.begin(); iterator != animations.end(); iterator++) {
        iterator->second->x = x;
        iterator->second->y = y;
    }

}

void NetworkedMonster::draw(sf::RenderWindow *app) {
    if(direction == "up") {
        animations["up"]->draw(app);
    }
    else if(direction == "down" ) {
        animations["down"]->draw(app);
    }
    else if(direction == "left") {
        animations["left"]->draw(app);
    }
    else if(direction == "right") {
        animations["right"]->draw(app);
    }	

}
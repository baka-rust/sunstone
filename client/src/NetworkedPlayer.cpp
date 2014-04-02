#include "NetworkedPlayer.h"

#include <iostream>

NetworkedPlayer::NetworkedPlayer(int xPos, int yPos, std::string dir) {

    tileX = xPos;
    tileY = yPos;

    x = tileX * 16;
    y = tileY * 16;

    direction = dir;

    animations["up"] = new AnimationSequence("resources/player/playerTest", 2, .25);
    animations["down"] = new AnimationSequence("resources/player/playerTest", 2, .25);
    animations["left"] = new AnimationSequence("resources/player/playerTest", 2, .25);
    animations["right"] = new AnimationSequence("resources/player/playerTest", 2, .25);

}

void NetworkedPlayer::update(float elapsedTime) {

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

void NetworkedPlayer::draw(sf::RenderWindow *app) {

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

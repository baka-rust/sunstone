#include "Player.h"

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

#include <iostream>

Player::Player(int xPos, int yPos, std::string dir) {

    tileX = xPos;
    tileY = yPos;

    x = tileX * 16;
    y = tileY * 16;

    direction = dir;

    //animations["up"] = new AnimationSequence("resources/player/up", 2, .25);
    //animations["down"] = new AnimationSequence("resources/player/down", 2, .25);
    //animations["left"] = new AnimationSequence("resources/player/left", 2, .25);
    //animations["right"] = new AnimationSequence("resources/player/right", 2, .25);

    std::string walkResource = "resources/player/walk";
    int walkFrames = 8;
    float walkSpeed = 0.02;
    
    animations["up"] = new AnimationSequence(walkResource, walkFrames, walkSpeed);
    animations["down"] = new AnimationSequence(walkResource, walkFrames, walkSpeed);
    animations["left"] = new AnimationSequence(walkResource, walkFrames, walkSpeed);
    animations["right"] = new AnimationSequence(walkResource, walkFrames, walkSpeed);

}

void Player::update(float elapsedTime) {

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

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && focused) {
        if(!moving) {
            if(terrain->getTile(tileX, tileY-1, "mid") == 0) {
                tileY = tileY - 1;
                moving = true;
            }
            direction = "up";
            network->updatePlayerLocation(tileX, tileY, direction);
        }
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && focused) {
        if(!moving) {
            if(terrain->getTile(tileX, tileY+1, "mid") == 0) {
                tileY = tileY + 1;
                moving = true;
            }
            direction = "down";
            network->updatePlayerLocation(tileX, tileY, direction);
        }
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && focused) {
        if(!moving) {
            if(terrain->getTile(tileX-1, tileY, "mid") == 0) {
                tileX = tileX - 1;
                moving = true;
            }
            direction = "left";
            network->updatePlayerLocation(tileX, tileY, direction);
        }
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && focused) {
        if(!moving) {
            if(terrain->getTile(tileX+1, tileY, "mid") == 0) {
                tileX = tileX + 1;
                moving = true;
            }
            direction = "right";
            network->updatePlayerLocation(tileX, tileY, direction);
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

void Player::draw(sf::RenderWindow *app) {

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

#include "Player.h"

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>
#include <iostream>

#include "Player/Directions.h"
#include "Player/States.h"

Player::Player(int xPos, int yPos, std::string dir) {

    tileX = xPos;
    tileY = yPos;

    x = tileX * 16;
    y = tileY * 16;

    if (dir == "up") {
        direction = Up;
    } else if (dir == "down") {
        direction = Down;
    } else if (dir == "left") {
        direction = Left;
    } else {
        direction = Right;
    }
    
    state = Idle;
    
    std::string idleResource = "resources/player/walk"; // TODO change
    int idleFrames = 1; // TODO change
    float idleSpeed = 0.01;
    
    std::string walkResource = "resources/player/walk";
    int walkFrames = 8;
    float walkSpeed = 0.02;
    
    std::string shootResource = "resources/player/walk"; // TODO change
    int shootFrames = 1; // TODO change
    float shootSpeed = 0.01;
    
    std::string dieResource = "resources/player/walk"; // TODO change
    int dieFrames = 1; // TODO change
    float dieSpeed = 0.01;
    
    // idle
    animations[Idle] = std::vector<AnimationSequence*>(4);
    animations[Idle][Up] = new AnimationSequence(idleResource, idleFrames, idleSpeed);
    animations[Idle][Down]  = new AnimationSequence(idleResource, idleFrames, idleSpeed);
    animations[Idle][Left] = new AnimationSequence(idleResource, idleFrames, idleSpeed);
    animations[Idle][Right] = new AnimationSequence(idleResource, idleFrames, idleSpeed);
    
    // walk
    animations[Walking] = std::vector<AnimationSequence*>(4);
    animations[Walking][Up]= new AnimationSequence(walkResource, walkFrames, walkSpeed);
    animations[Walking][Down] = new AnimationSequence(walkResource, walkFrames, walkSpeed);
    animations[Walking][Right] = new AnimationSequence(walkResource, walkFrames, walkSpeed);
    animations[Walking][Left] = new AnimationSequence(walkResource, walkFrames, walkSpeed);
    
    // shoot
    animations[Firing] = std::vector<AnimationSequence*>(4);
    animations[Firing][Up] = new AnimationSequence(shootResource, shootFrames, shootSpeed);
    animations[Firing][Down] = new AnimationSequence(shootResource, shootFrames, shootSpeed);
    animations[Firing][Left] = new AnimationSequence(shootResource, shootFrames, shootSpeed);
    animations[Firing][Right] = new AnimationSequence(shootResource, shootFrames, shootSpeed);
    
    // die
    AnimationSequence* dying = new AnimationSequence(dieResource, dieFrames, dieSpeed);
    animations[Dying] = std::vector<AnimationSequence*>(4, dying);
}

void Player::update(float elapsedTime) {
    state = Idle;
    
    if(direction == Up) {
        if(y <= (tileY * 16)) {
            onTile = true;
        }
        else {
            onTile = false;
            state = Walking;
            y = y - (speed * elapsedTime);
            animations[Walking][direction]->update(elapsedTime);
        }
    }
    else if(direction == Down) {
        if(y >= (tileY * 16)) {
            onTile = true;
        }
        else {
            onTile = false;
            state = Walking;
            y = y + (speed * elapsedTime);
            animations[Walking][direction]->update(elapsedTime);
        }
    }
    else if(direction == Left) {
        if(x <= (tileX * 16)) {
            onTile = true;
        }
        else {
            onTile = false;
            state = Walking;
            x = x - (speed * elapsedTime);
            animations[Walking][direction]->update(elapsedTime);
        }
    }
    else if(direction == Right) {
        if(x >= (tileX * 16)) {
            onTile = true;
        }
        else {
            onTile = false;
            state = Walking;
            x = x + (speed * elapsedTime);
            animations[Walking][direction]->update(elapsedTime);
        }
    }

    // Handle user input
    if(state != Walking && focused) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && focused) {
            if(terrain->getTile(tileX, tileY-1, "mid") == 0) {
                tileY = tileY - 1;
                state = Walking;
            }
            
            direction = Up;
            network->updatePlayerLocation(tileX, tileY, "up");
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if(terrain->getTile(tileX, tileY+1, "mid") == 0) {
                tileY = tileY + 1;
                state = Walking;
            }
            
            direction = Down;
            network->updatePlayerLocation(tileX, tileY, "down");
            
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if(terrain->getTile(tileX-1, tileY, "mid") == 0) {
                tileX = tileX - 1;
                state = Walking;
            }
            
            direction = Left;
            network->updatePlayerLocation(tileX, tileY, "down");
            
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if(terrain->getTile(tileX+1, tileY, "mid") == 0) {
                tileX = tileX + 1;
                state = Walking;
            }
            
            direction = Right;
            network->updatePlayerLocation(tileX, tileY, "right");
            
        }
    }
    
    if(state != Walking && onTile) {
        x = tileX * 16;
        y = tileY * 16;
    }

    // set animation positions
    for(auto row : animations) {
        for(auto col : row) {
            col->x = x;
            col->y = y;
        }
    }

}

void Player::draw(sf::RenderWindow *app) {
    animations[state][direction]->draw(app);
}

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
        direction = N;
    } else if (dir == "down") {
        direction = S;
    } else if (dir == "left") {
        direction = W;
    } else {
        direction = E;
    }
    
    state = Idle;
    
    std::string idleResource = "resources/player/idle";
    int idleFrames = 1;
    float idleSpeed = 1.0;
    
    std::string walkResource = "resources/player/walk";
    int walkFrames = 8;
    float walkSpeed = 0.02  ;
    
    std::string shootResource = "resources/player/fireEast";
    int shootFrames = 6;
    float shootSpeed = 0.02;
    
    std::string dieResource = "resources/player/die";
    int dieFrames = 98;
    float dieSpeed = 0.05;
    
    // idle
    animations[Idle] = std::vector<AnimationSequence*>(4);
    animations[Idle][N] = new AnimationSequence(idleResource + "North", idleFrames, idleSpeed);
    animations[Idle][S] = new AnimationSequence(idleResource + "South", idleFrames, idleSpeed);
    animations[Idle][W] = new AnimationSequence(idleResource + "West", idleFrames, idleSpeed);
    animations[Idle][E] = new AnimationSequence(idleResource + "East", idleFrames, idleSpeed);
    
    // walk
    animations[Walking] = std::vector<AnimationSequence*>(4);
    animations[Walking][N] = new AnimationSequence(walkResource + "North", walkFrames, walkSpeed);
    animations[Walking][S] = new AnimationSequence(walkResource + "East", walkFrames, walkSpeed);
    animations[Walking][W] = new AnimationSequence(walkResource + "West", walkFrames, walkSpeed);
    animations[Walking][E] = new AnimationSequence(walkResource + "East", walkFrames, walkSpeed);
    
    // shoot
    animations[Firing] = std::vector<AnimationSequence*>(4);
    animations[Firing][N] = new AnimationSequence(shootResource, shootFrames, shootSpeed);
    animations[Firing][S] = new AnimationSequence(shootResource, shootFrames, shootSpeed);
    animations[Firing][W] = new AnimationSequence(shootResource, shootFrames, shootSpeed);
    animations[Firing][E] = new AnimationSequence(shootResource, shootFrames, shootSpeed);
    
    // die
    AnimationSequence* dying = new AnimationSequence(dieResource, dieFrames, dieSpeed);
    animations[Dying] = std::vector<AnimationSequence*>(4, dying);
}

void Player::update(float elapsedTime) {
    state = Idle;
    
    if(direction == N) {
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
    else if(direction == S) {
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
    else if(direction == W) {
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
    else if(direction == E) {
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
            
            direction = N;
            network->updatePlayerLocation(tileX, tileY, "up");
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if(terrain->getTile(tileX, tileY+1, "mid") == 0) {
                tileY = tileY + 1;
                state = Walking;
            }
            
            direction = S;
            network->updatePlayerLocation(tileX, tileY, "down");
            
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if(terrain->getTile(tileX-1, tileY, "mid") == 0) {
                tileX = tileX - 1;
                state = Walking;
            }
            
            direction = W;
            network->updatePlayerLocation(tileX, tileY, "down");
            
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if(terrain->getTile(tileX+1, tileY, "mid") == 0) {
                tileX = tileX + 1;
                state = Walking;
            }
            
            direction = E;
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

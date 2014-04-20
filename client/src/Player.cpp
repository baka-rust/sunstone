#include "Player/Player.h"

#include <string>

Player::Player(int x, int y, std::string dir) {
    Direction direction;
    
    if (dir == "up") {
        direction = N;
    } else if (dir == "down") {
        direction = S;
    } else if (dir == "left") {
        direction = W;
    } else {
        direction = E;
    }
    
    Player(x, y, direction);
}

Player::Player(int x, int y, Direction dir) {
    // Init variables
    this->tileX = x;
    this->tileY = y;
    
    this->x = this->tileX * 16;
    this->y = this->tileY * 16;
    
    this->direction = dir;
    this->state = Idle;
    
    // Init animations
    std::string idleResource = "resources/player/idle";
    int idleFrames = 1;
    float idleSpeed = 1.0;
    
    std::string walkResource = "resources/player/walk";
    int walkFrames = 8;
    float walkSpeed = 0.02  ;
    
    std::string shootResource = "resources/player/fire";
    int shootFrames = 5;
    float shootSpeed = 0.02;
    
    std::string dieResource = "resources/player/die";
    int dieFrames = 98;
    float dieSpeed = 0.05;
    
    // idle
    animations[Idle] = std::vector<AnimationSequence*>(4);
    animations[Idle][N] = new AnimationSequence(idleResource, idleFrames, idleSpeed);
    animations[Idle][S] = new AnimationSequence(idleResource, idleFrames, idleSpeed);
    animations[Idle][W] = new AnimationSequence(idleResource, idleFrames, idleSpeed);
    animations[Idle][E] = new AnimationSequence(idleResource, idleFrames, idleSpeed);
    
    // walk
    animations[Walking] = std::vector<AnimationSequence*>(4);
    animations[Walking][N]= new AnimationSequence(walkResource, walkFrames, walkSpeed);
    animations[Walking][S] = new AnimationSequence(walkResource, walkFrames, walkSpeed);
    animations[Walking][W] = new AnimationSequence(walkResource + "West", walkFrames, walkSpeed);
    animations[Walking][E] = new AnimationSequence(walkResource, walkFrames, walkSpeed);
    
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

Direction Player::getDirection() {
    return this->direction;
};

float Player::getX() {
    return this->x;
};

float Player::getY() {
    return this->y;
};

int Player::getTileX() {
    return this->tileX;
};

int Player::getTileY() {
    return this->tileY;
};
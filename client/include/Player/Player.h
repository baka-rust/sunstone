#ifndef LOCALPLAYER_H
#define LOCALPLAYER_H

#include <string>

#include "States.h"
#include "Directions.h"
#include "../AnimationSequence.h"

class Player {
    public:
        Player(int x, int y, std::string dir) : Player(x, y, stringToDirection(dir)) {};
        Player(int x, int y, Direction dir);
    
        virtual void update(float elapsedTime);
        void draw(sf::RenderWindow *app);
    
        Direction getDirection();
        Direction stringToDirection(std::string dir);
    
        float getX();
        float getY();
    
        int getTileX();
        int getTileY();
    
    protected:
        float x;
        float y;
        
        int tileX;
        int tileY;
        bool onTile;
        
        Direction direction;
        State state;
        int speed;
        
        std::vector<std::vector<AnimationSequence*> > animations = std::vector<std::vector<AnimationSequence*>>(4);
    
        void updateAnimations(float elapsedTime);
        void updatePositions(float elapsedTime);
};

#endif // LOCALPLAYER_H
#ifndef NETWORKEDPLAYER_H
#define NETWORKEDPLAYER_H

#include <string>
#include <vector>
#include <map>

#include "Player/Directions.h"
#include "Player/States.h"
#include "AnimationSequence.h"
#include "Terrain.h"

class NetworkedPlayer {

    public:

        float x, y;
        int tileX, tileY;
        int speed = 40;
        bool onTile = true;

        Direction direction;
        State state;

        NetworkedPlayer(int xPos, int yPos, std::string dir);
        
        void update(float elapsedTime);
        void draw(sf::RenderWindow *app);

    private:
        std::vector<std::vector<AnimationSequence*> > animations = std::vector<std::vector<AnimationSequence*>>(4);

};

#endif // NETWORKEDPLAYER_H

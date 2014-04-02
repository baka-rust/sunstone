#ifndef NETWORKEDPLAYER_H
#define NETWORKEDPLAYER_H

#include <string>
#include <vector>
#include <map>

#include "AnimationSequence.h"
#include "Terrain.h"

class NetworkedPlayer {

    public:

        float x, y;
        int tileX, tileY;
        int speed = 40;
        std::string direction;
        bool onTile = true;

        sf::Sprite spriteLeft, spriteRight, spriteUp, spriteDown;

        NetworkedPlayer(int xPos, int yPos, std::string dir);
        void update(float elapsedTime);
        void draw(sf::RenderWindow *app);

    private:

        std::map<std::string, AnimationSequence*> animations;
        typedef std::map<std::string, AnimationSequence*>::iterator i_animations;

};

#endif // NETWORKEDPLAYER_H

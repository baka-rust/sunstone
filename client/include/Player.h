#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <string>
#include <vector>
#include <map>

#include "AnimationSequence.h"
#include "Terrain.h"
#include "Network.h"

class Terrain;
class Network;

extern bool focused;

class Player {

    public:

        float x, y;
        int tileX, tileY;
        int speed = 40; // rely on stats later
        std::string direction;
        bool onTile = true;

        Terrain *terrain; // we should figure out a better way to handle this. singletons in cpp are dumb.
        Network *network;

        sf::Sprite spriteLeft, spriteRight, spriteUp, spriteDown;

        Player(int xPos, int yPos, std::string dir);
        void update(float elapsedTime);
        void draw(sf::RenderWindow *app);

    private:

        std::map<std::string, AnimationSequence*> animations;
        typedef std::map<std::string, AnimationSequence*>::iterator i_animations;

};

#endif // PLAYER_H

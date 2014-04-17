#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <string>
#include <vector>
#include <map>

#include "Player/Directions.h"
#include "Player/States.h"
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
        bool onTile = true;
    
        Direction direction;
        State state;

        Terrain *terrain; // we should figure out a better way to handle this. singletons in cpp are dumb.
        Network *network;

        Player(int xPos, int yPos, std::string dir);
    
        void update(float elapsedTime);
        void draw(sf::RenderWindow *app);

    private:
        std::vector<std::vector<AnimationSequence*> > animations = std::vector<std::vector<AnimationSequence*>>(4);
};

#endif // PLAYER_H

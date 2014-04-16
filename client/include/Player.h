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
        Direction direction;
        State state;
        bool onTile = true;

        Terrain *terrain; // we should figure out a better way to handle this. singletons in cpp are dumb.
        Network *network;

        sf::Sprite spriteLeft, spriteRight, spriteUp, spriteDown;

        Player(int xPos, int yPos, std::string dir);
        void update(float elapsedTime);
        void draw(sf::RenderWindow *app);

    private:

        std::vector<std::vector<AnimationSequence*> > animations = std::vector<std::vector<AnimationSequence*>>(4);
        typedef std::vector<std::vector<AnimationSequence*> >::iterator i_anim_row;
        typedef std::vector<AnimationSequence*>::iterator i_anim_col;

};

#endif // PLAYER_H

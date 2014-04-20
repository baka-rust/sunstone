#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <string>
#include <vector>
#include <map>

#include "Player/Player.h"
#include "Player/Directions.h"
#include "Player/States.h"
#include "AnimationSequence.h"
#include "Terrain.h"
#include "Network.h"

class Terrain;
class Network;

extern bool focused;

class LocalPlayer : public Player {

    public:
        typedef Player super;
    
        Terrain *terrain; // we should figure out a better way to handle this. singletons in cpp are dumb.
        Network *network;
    
        LocalPlayer(int x, int y, std::string dir) : super(x, y, dir) {};
        LocalPlayer(int x, int y, Direction dir) : super(x, y, dir) {};
    
        virtual void update(float elapsedTime);
};

#endif // PLAYER_H

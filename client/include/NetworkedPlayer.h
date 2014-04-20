#ifndef NETWORKEDPLAYER_H
#define NETWORKEDPLAYER_H

#include <string>
#include <vector>
#include <map>

#include "Player/Player.h"
#include "Player/Directions.h"
#include "AnimationSequence.h"
#include "Terrain.h"

class NetworkedPlayer : public Player {
    public:
        typedef Player super;
    
        NetworkedPlayer(int x, int y, std::string dir) : super(x, y, dir) {};
        NetworkedPlayer(int x, int y, Direction dir) : super(x, y, dir) {};
    
        void setTileX(int x);
        void setTileY(int y);

        void setDirection(std::string dir);
        void setDirection(Direction dir);
};

#endif // NETWORKEDPLAYER_H

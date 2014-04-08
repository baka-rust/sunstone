#include <SFML/System.hpp>

#include "Network.h"
#include "Dungeon.h"
#include "PathMapper.h"

int main() {

    Dungeon d(20,20,6,8,5);
    d.create();
    
    PathMapper p(&d);
    p.createMap(0, 12, 4);
    
    
//    Network network;
//
//    network.run();

    return 0;
}

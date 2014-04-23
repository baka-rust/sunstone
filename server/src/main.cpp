#include <SFML/System.hpp>

#include "Network.h"

//#include <time.h>
#include <ctime>
#include "Dungeon.h"
#include "PathMaster.h"

int main() {

    
//    clock_t start = clock();
//    Dungeon d(128,128,6,8,3111);
//    d.create();
//    clock_t end = clock();
//    std::cout << (double) (end-start) / CLOCKS_PER_SEC * 1000.0 << "\n";
//
//    start = clock();
//    PathMaster p(&d);
//    end = clock();
//    std::cout << (double) (end-start) / CLOCKS_PER_SEC * 1000.0 << "\n";
//
//    start = clock();
//    p.createMap(0, 65, 65);
//    end = clock();
//    std::cout << (double) (end-start) / CLOCKS_PER_SEC * 1000.0 << "\n";
//
//    start = clock();
//    p.createMap(0, 65, 65);
//    end = clock();
//    std::cout << (double) (end-start) / CLOCKS_PER_SEC * 1000.0 << "\n";
    
    Network network;

    network.run();

    return 0;
}

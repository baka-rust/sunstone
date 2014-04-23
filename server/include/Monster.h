#ifndef MONSTER_H
#define MONSTER_H

#include <SFML/Network.hpp>

#include <string>

class Monster {

    public:
        int x;
        int y;
        std::string direction;

        Monster(int x, int y, std::string direction)
        : x(x), y(y), direction(direction) {};

};

#endif // MONSTER_H

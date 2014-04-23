#ifndef VISION_H
#define VISION_H

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

class Vision {
    public:
        Vision();
    private:
        static const int width = 128;
        static const int height = 128;
        bool grid[width][height];
};

#endif // VISION_H
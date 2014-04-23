#include "Vision.h"

Vision::Vision() {
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            grid[i][j] = false;
        }
    }
}
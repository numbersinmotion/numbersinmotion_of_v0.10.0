#pragma once

#include "ofMain.h"

class hexagon {
    
public:
    
    hexagon(glm::vec2 _center, float _x, float _y, float _z, int _i, int _j, int _k);
    void draw();
    
    glm::vec2 center, xDir, yDir, zDir;
    float x, y, z;
    int i, j, k;
};

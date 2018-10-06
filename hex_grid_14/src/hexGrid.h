#pragma once

#include "ofMain.h"
#include "hexagon.h"

class hexGrid {
    
public:
    
    hexGrid(glm::vec2 _center, int _xCount, int _yCount, int _zCount);
    
    void updateTiling();
    
    glm::vec2 center, xDir, yDir, zDir;
    int xCount, yCount, zCount;
    vector<hexagon> tiling;
    vector<float> xSizes, ySizes, zSizes;
    
};

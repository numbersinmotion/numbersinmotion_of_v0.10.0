#include "hexGrid.h"

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

hexGrid::hexGrid(glm::vec2 _center, int _xCount, int _yCount, int _zCount) {
    
    center = _center;
    xCount = _xCount;
    yCount = _yCount;
    zCount = _zCount;
    
//    for (int i = 0; i < 2 * xCount + 1; i++) xSizes.push_back(10.0);
//    for (int i = 0; i < 2 * yCount + 1; i++) ySizes.push_back(10.0);
//    for (int i = 0; i < 2 * zCount + 1; i++) zSizes.push_back(10.0);
    for (int i = 0; i < 2 * xCount + 1; i++) xSizes.push_back(ofRandom(10, 20));
    for (int i = 0; i < 2 * yCount + 1; i++) ySizes.push_back(ofRandom(10, 20));
    for (int i = 0; i < 2 * zCount + 1; i++) zSizes.push_back(ofRandom(10, 20));
    
    xDir = glm::vec2(cos(0 * 2 * PI / 3 + PI / 6), sin(0 * 2 * PI / 3 + PI / 6));
    yDir = glm::vec2(cos(1 * 2 * PI / 3 + PI / 6), sin(1 * 2 * PI / 3 + PI / 6));
    zDir = glm::vec2(cos(2 * 2 * PI / 3 + PI / 6), sin(2 * 2 * PI / 3 + PI / 6));
    
    updateTiling();
    
}

void hexGrid::updateTiling() {

    tiling.clear();
    
    for (int i = -xCount; i <= xCount; i++) {
        for (int j = -yCount; j <= yCount; j++) {
            int k = -1 * (i + j);
            if (abs(k) <= zCount) {
                glm::vec2 hexCenter = center;
                if (sgn(i) == 1) for (int s = 0; s < i; s++) hexCenter += xSizes[xCount + s] * xDir;
                if (sgn(j) == 1) for (int s = 0; s < j; s++) hexCenter += ySizes[yCount + s] * yDir;
                if (sgn(k) == 1) for (int s = 0; s < k; s++) hexCenter += zSizes[zCount + s] * zDir;
                if (sgn(i) == -1) for (int s = 0; s > i; s--) hexCenter -= xSizes[xCount + s - 1] * xDir;
                if (sgn(j) == -1) for (int s = 0; s > j; s--) hexCenter -= ySizes[yCount + s - 1] * yDir;
                if (sgn(k) == -1) for (int s = 0; s > k; s--) hexCenter -= zSizes[zCount + s - 1] * zDir;
                
                hexagon tmp(hexCenter, xSizes[i + xCount], ySizes[j + yCount], zSizes[k + zCount], i, j, k);
                tiling.push_back(tmp);
            }
        }
    }
    
}

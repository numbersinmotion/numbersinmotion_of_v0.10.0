#include "hexagon.h"

hexagon::hexagon(glm::vec2 _center, float _x, float _y, float _z, int _i, int _j, int _k) {
    
    center = _center;
    x = _x;
    y = _y;
    z = _z;
    i = _i;
    j = _j;
    k = _k;
    
    xDir = glm::vec2(cos(0 * 2 * PI / 3 + PI / 6), sin(0 * 2 * PI / 3 + PI / 6));
    yDir = glm::vec2(cos(1 * 2 * PI / 3 + PI / 6), sin(1 * 2 * PI / 3 + PI / 6));
    zDir = glm::vec2(cos(2 * 2 * PI / 3 + PI / 6), sin(2 * 2 * PI / 3 + PI / 6));
    
}

void hexagon::draw() {
    
    ofSetColor(255);
    
    ofDrawLine(center, center + x * xDir);
    ofDrawLine(center + x * xDir, center + x * xDir + y * yDir);
    ofDrawLine(center + x * xDir + y * yDir, center + y * yDir);

    ofDrawLine(center, center + y * yDir);
    ofDrawLine(center + y * yDir, center + y * yDir + z * zDir);
    ofDrawLine(center + y * yDir + z * zDir, center + z * zDir);

    ofDrawLine(center, center + z * zDir);
    ofDrawLine(center + z * zDir, center + z * zDir + x * xDir);
    ofDrawLine(center + z * zDir + x * xDir, center + x * xDir);
    
}

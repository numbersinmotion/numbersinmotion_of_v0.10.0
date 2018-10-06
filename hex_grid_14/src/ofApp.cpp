#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(0);
    
    ofTrueTypeFont font;
    font.load("gt-walsheim-thin-oblique.ttf", 500, true, true, true);
    
    letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    for (int i = 0; i < letters.size(); i++) {
        
        char c = letters[i];
        
        ofRectangle bb = font.getStringBoundingBox(ofToString(c), 0, 0);
        
        ofFbo tmpFbo;
        
        float sideLength = 2 * sqrt(pow(bb.getWidth() / 2, 2) + pow(bb.getHeight() / 2, 2));
        
        tmpFbo.allocate(sideLength, sideLength, GL_RGBA);
        
        tmpFbo.begin();
        
        ofClear(0, 0, 0, 255);
        
        ofSetColor(255);
        
        font.drawString(ofToString(c), -bb.x + (sideLength - bb.getWidth()) / 2, -bb.y + (sideLength - bb.getHeight()) / 2);
        
        tmpFbo.end();
        
        fbos.push_back(tmpFbo);
        
    }
    
    t = 0;
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

    int tileCount = 25;
    hexGrid hg(glm::vec2(0, 0), tileCount, tileCount, tileCount);
    t = 0.2 * ofGetElapsedTimef();

    float xPlus = 0;
    float yPlus = 0;
    float zPlus = 0;

    hg.xSizes.clear();
    float xTotal = 0;
    for (int i = -hg.xCount; i <= hg.xCount; i++) {
        float size = 1000 * pow(ofNoise(i / 5.0, 100, t, 100), 5) + xPlus;
        hg.xSizes.push_back(size);
        xTotal += size;
    }
    for (int i = 0; i < hg.xSizes.size(); i++) hg.xSizes[i] *= 1200 / xTotal;

    hg.ySizes.clear();
    float yTotal = 0;
    for (int i = -hg.yCount; i <= hg.yCount; i++) {
        float size = 1000 * pow(ofNoise(i / 5.0, 200, t, 500), 5) + yPlus;
        hg.ySizes.push_back(size);
        yTotal += size;
    }
    for (int i = 0; i < hg.ySizes.size(); i++) hg.ySizes[i] *= 1200 / yTotal;

    hg.zSizes.clear();
    float zTotal = 0;
    for (int i = -hg.zCount; i <= hg.zCount; i++) {
        float size = 1000 * pow(ofNoise(i / 5.0, 300, t, 900), 5) + zPlus;
        hg.zSizes.push_back(size);
        zTotal += size;
    }
    for (int i = 0; i < hg.zSizes.size(); i++) hg.zSizes[i] *= 1200 / zTotal;

    hg.updateTiling();
    
    glm::vec2 recenter(0, 0);
    int counter = 0;
    for (int i = 0; i < hg.tiling.size(); i++) {
        hexagon h = hg.tiling[i];
        if (abs(h.i) == hg.xCount || abs(h.j) == hg.yCount || abs(h.k) == hg.zCount) {
            counter++;
            recenter += h.center;
        }
    }
    recenter /= counter;
    ofTranslate(-recenter.x, -recenter.y);

    for (int i = 0; i < hg.tiling.size(); i++) {

        hexagon h = hg.tiling[i];

        float shrink = 1;
        float minDist = MIN(h.x, MIN(h.y, h.z));
        glm::vec2 p1 = h.center + shrink * (minDist * h.xDir);
        glm::vec2 p2 = h.center + shrink * (minDist * h.xDir + minDist * h.yDir);
        glm::vec2 p3 = h.center + shrink * (minDist * h.yDir);
        glm::vec2 p4 = h.center + shrink * (minDist * h.yDir + minDist * h.zDir);
        glm::vec2 p5 = h.center + shrink * (minDist * h.zDir);
        glm::vec2 p6 = h.center + shrink * (minDist * h.zDir + minDist * h.xDir);

        ofFbo tmpFbo = fbos[floor(ofMap(ofNoise(i, i), 0, 1, 0, letters.size()))];
        
        float rotation = 2 * PI * ofNoise(i, i, 100) + PI;
        glm::vec2 t1 = glm::vec2(tmpFbo.getWidth() / 2.0 * cos(0.0 / 6.0 * 2 * PI + rotation), tmpFbo.getWidth() / 2.0 * sin(0.0 / 6.0 * 2 * PI + rotation)) + glm::vec2(tmpFbo.getWidth() / 2, tmpFbo.getHeight() / 2);
        glm::vec2 t2 = glm::vec2(tmpFbo.getWidth() / 2.0 * cos(1.0 / 6.0 * 2 * PI + rotation), tmpFbo.getWidth() / 2.0 * sin(1.0 / 6.0 * 2 * PI + rotation)) + glm::vec2(tmpFbo.getWidth() / 2, tmpFbo.getHeight() / 2);
        glm::vec2 t3 = glm::vec2(tmpFbo.getWidth() / 2.0 * cos(2.0 / 6.0 * 2 * PI + rotation), tmpFbo.getWidth() / 2.0 * sin(2.0 / 6.0 * 2 * PI + rotation)) + glm::vec2(tmpFbo.getWidth() / 2, tmpFbo.getHeight() / 2);
        glm::vec2 t4 = glm::vec2(tmpFbo.getWidth() / 2.0 * cos(3.0 / 6.0 * 2 * PI + rotation), tmpFbo.getWidth() / 2.0 * sin(3.0 / 6.0 * 2 * PI + rotation)) + glm::vec2(tmpFbo.getWidth() / 2, tmpFbo.getHeight() / 2);
        glm::vec2 t5 = glm::vec2(tmpFbo.getWidth() / 2.0 * cos(4.0 / 6.0 * 2 * PI + rotation), tmpFbo.getWidth() / 2.0 * sin(4.0 / 6.0 * 2 * PI + rotation)) + glm::vec2(tmpFbo.getWidth() / 2, tmpFbo.getHeight() / 2);
        glm::vec2 t6 = glm::vec2(tmpFbo.getWidth() / 2.0 * cos(5.0 / 6.0 * 2 * PI + rotation), tmpFbo.getWidth() / 2.0 * sin(5.0 / 6.0 * 2 * PI + rotation)) + glm::vec2(tmpFbo.getWidth() / 2, tmpFbo.getHeight() / 2);

        ofMesh tmpMesh;
        tmpMesh.setMode(OF_PRIMITIVE_TRIANGLES);

        tmpMesh.addVertex(glm::vec3(h.center.x, h.center.y, 0));
        tmpMesh.addTexCoord(tmpFbo.getTexture().getCoordFromPoint(tmpFbo.getWidth() / 2, tmpFbo.getHeight() / 2));
        tmpMesh.addVertex(glm::vec3(p1.x, p1.y, 0));
        tmpMesh.addTexCoord(tmpFbo.getTexture().getCoordFromPoint(t1.x, t1.y));
        tmpMesh.addVertex(glm::vec3(p2.x, p2.y, 0));
        tmpMesh.addTexCoord(tmpFbo.getTexture().getCoordFromPoint(t2.x, t2.y));

        tmpMesh.addVertex(glm::vec3(h.center.x, h.center.y, 0));
        tmpMesh.addTexCoord(tmpFbo.getTexture().getCoordFromPoint(tmpFbo.getWidth() / 2, tmpFbo.getHeight() / 2));
        tmpMesh.addVertex(glm::vec3(p2.x, p2.y, 0));
        tmpMesh.addTexCoord(tmpFbo.getTexture().getCoordFromPoint(t2.x, t2.y));
        tmpMesh.addVertex(glm::vec3(p3.x, p3.y, 0));
        tmpMesh.addTexCoord(tmpFbo.getTexture().getCoordFromPoint(t3.x, t3.y));

        tmpMesh.addVertex(glm::vec3(h.center.x, h.center.y, 0));
        tmpMesh.addTexCoord(tmpFbo.getTexture().getCoordFromPoint(tmpFbo.getWidth() / 2, tmpFbo.getHeight() / 2));
        tmpMesh.addVertex(glm::vec3(p3.x, p3.y, 0));
        tmpMesh.addTexCoord(tmpFbo.getTexture().getCoordFromPoint(t3.x, t3.y));
        tmpMesh.addVertex(glm::vec3(p4.x, p4.y, 0));
        tmpMesh.addTexCoord(tmpFbo.getTexture().getCoordFromPoint(t4.x, t4.y));

        tmpMesh.addVertex(glm::vec3(h.center.x, h.center.y, 0));
        tmpMesh.addTexCoord(tmpFbo.getTexture().getCoordFromPoint(tmpFbo.getWidth() / 2, tmpFbo.getHeight() / 2));
        tmpMesh.addVertex(glm::vec3(p4.x, p4.y, 0));
        tmpMesh.addTexCoord(tmpFbo.getTexture().getCoordFromPoint(t4.x, t4.y));
        tmpMesh.addVertex(glm::vec3(p5.x, p5.y, 0));
        tmpMesh.addTexCoord(tmpFbo.getTexture().getCoordFromPoint(t5.x, t5.y));

        tmpMesh.addVertex(glm::vec3(h.center.x, h.center.y, 0));
        tmpMesh.addTexCoord(tmpFbo.getTexture().getCoordFromPoint(tmpFbo.getWidth() / 2, tmpFbo.getHeight() / 2));
        tmpMesh.addVertex(glm::vec3(p5.x, p5.y, 0));
        tmpMesh.addTexCoord(tmpFbo.getTexture().getCoordFromPoint(t5.x, t5.y));
        tmpMesh.addVertex(glm::vec3(p6.x, p6.y, 0));
        tmpMesh.addTexCoord(tmpFbo.getTexture().getCoordFromPoint(t6.x, t6.y));

        tmpMesh.addVertex(glm::vec3(h.center.x, h.center.y, 0));
        tmpMesh.addTexCoord(tmpFbo.getTexture().getCoordFromPoint(tmpFbo.getWidth() / 2, tmpFbo.getHeight() / 2));
        tmpMesh.addVertex(glm::vec3(p6.x, p6.y, 0));
        tmpMesh.addTexCoord(tmpFbo.getTexture().getCoordFromPoint(t6.x, t6.y));
        tmpMesh.addVertex(glm::vec3(p1.x, p1.y, 0));
        tmpMesh.addTexCoord(tmpFbo.getTexture().getCoordFromPoint(t1.x, t1.y));

        tmpFbo.getTexture().bind();
        tmpMesh.draw();
        tmpFbo.getTexture().unbind();

    }
    
    
    
    
//    ofFbo tmpFbo = fbos[0];
//
//    ofMesh tmpMesh;
//    tmpMesh.setMode(OF_PRIMITIVE_TRIANGLES);
//
//    tmpMesh.addVertex(glm::vec3(0, 0, 0));
//    tmpMesh.addTexCoord(tmpFbo.getTexture().getCoordFromPoint(0, 0));
//
//    tmpMesh.addVertex(glm::vec3(tmpFbo.getWidth(), 0, 0));
//    tmpMesh.addTexCoord(tmpFbo.getTexture().getCoordFromPoint(tmpFbo.getWidth(), 0));
//
//    tmpMesh.addVertex(glm::vec3(0, tmpFbo.getHeight(), 0));
//    tmpMesh.addTexCoord(tmpFbo.getTexture().getCoordFromPoint(0, tmpFbo.getHeight()));
//
//    tmpMesh.addVertex(glm::vec3(tmpFbo.getWidth(), 0, 0));
//    tmpMesh.addTexCoord(tmpFbo.getTexture().getCoordFromPoint(tmpFbo.getWidth(), 0));
//
//    tmpMesh.addVertex(glm::vec3(0, tmpFbo.getHeight(), 0));
//    tmpMesh.addTexCoord(tmpFbo.getTexture().getCoordFromPoint(0, tmpFbo.getHeight()));
//
//    tmpMesh.addVertex(glm::vec3(tmpFbo.getWidth(), tmpFbo.getHeight(), 0));
//    tmpMesh.addTexCoord(tmpFbo.getTexture().getCoordFromPoint(tmpFbo.getWidth(), tmpFbo.getHeight()));
//
//    tmpFbo.getTexture().bind();
//    tmpMesh.draw();
//    tmpFbo.unbind();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

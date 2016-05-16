//
//  ParticleSpecs.hpp
//  visuals002
//
//  Created by Rico on 19.01.16.
//
//
#include "ofMain.h"

class ParticleSpecs{
public:
    ParticleSpecs();
    ~ParticleSpecs();
    
    void drawSphere();
    void drawCircle();
    void drawSubparticleLine();
    void drawSubparticleMesh();
    void drawHistoryLine();
    void drawPastCircle();
    
    void setHistoryLineWidth(float newWidth){
        historyLineWidth = newWidth;
    }
    void setSubparticleLineWidth(float newWidth){
        subparticleLineWidth = newWidth;
    }
    
    void setSubparticleLineVisible(bool newVisible){
        subparticleLineVisible = newVisible;
    }
    void setHistoryVisible(bool newVisible){
        historyVisible = newVisible;
    }
    void setCircleVisible(bool newVisible){
        circleVisible = newVisible;
    }
    void setRadius(float newRadius){
        radius = newRadius;
    }
    
    float radius;
    bool historyVisible;
    bool circleVisible;
    bool sphereVisible;
    bool subparticleLineVisible;
    
    float subparticleLineWidth;
    float historyLineWidth;
    
    int pastIndex;
        
    void setSpecs(ParticleSpecs& specs);
    //void set(ParticleSpecs& specs);
    void isItMe(ParticleSpecs& spec){
        if (&spec == this) {
            return true;
        } else {
            return false;
        }
    }
};
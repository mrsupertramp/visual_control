//
//  Particle.hpp
//  visuals002
//
//  Created by Rico on 08.12.15.
//
//

#pragma once
#define Launchpad_hpp

#include "ofMain.h"
#include "ofMesh.h"
#include "ColorPalette.hpp"
#include "ParticlePhysics.hpp"
#include "ParticleSpecs.hpp"
#include "Constants.h"


class Particle : public ParticlePhysics, public ParticleSpecs{
public:
    Particle();
    ~Particle();
    
    void update();
    void update(ofVec3f posParent, ofVec3f velParent);
    
    void subparticleGravitation();

    void setSubparticleStatus(int newBehavior);
    
    void draw();
    void drawSphere();
    void drawWireFrameSphere();
    void drawCircle();
    void drawSubparticleLine();
    void drawSubparticleMesh();
    void drawHistoryLine();
    void drawPastCircle();
    
    uint64_t getTimeAlive(){
        return ofGetElapsedTimeMillis() - timeBorn;
    }
    uint64_t getTimeLeft(){
        return lifeTime - getTimeAlive();
    }
    
    void generateParticle(ofVec3f pos, ofVec3f vel);
    void eliminateParticle(int index);
    
    void generateWave(ofVec3f pos, ofVec3f velDir, float ampl, float stiff, float drag);
    
    ParticleSpecs* subSpecs;
    
    ParticlePhysics* subPhysics;
    
    vector <ofVec3f> posHistory;
    vector <ofVec3f> velHistory;
    
    vector <Particle> subparticle;
    
    ofIcoSpherePrimitive icoSphere;
    
    uint64_t lifeTime = 0;
    
    ofMaterial material;

private:
    
    uint64_t timeBorn;
    ColorPalette colorPal;
    
    ofVec3f parentPosition;
    ofVec3f parentVelocity;
    
    void saveHistory();
    bool saveHistoryEnabled = true;
    int tLastHistorySave;
    int saveHistoryIntervall = 16;
    int historyMaxSize = 70;
    
    ofMesh historyMesh;
    
    //ParticleMesh mesh;
    
    ofMesh subparticleTessellation;
    
};


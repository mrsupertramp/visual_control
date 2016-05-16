//
//  ParticlePhysics.hpp
//  visuals002
//
//  Created by Rico on 19.01.16.
//
//
#pragma once

#include "ofMain.h"
#include "Constants.h"

class ParticlePhysics{
public:
    
    ParticlePhysics();
    ~ParticlePhysics();
    
    void move(ofVec3f velocity);
    void vibrate(ofVec3f dir);
    void moveNoise();
    void centralForce();
    void accelerateToVelocity(ofVec3f a, float velMax);
    
    void setVelocityLength(float velMax){
        velocity = velocity.normalize() * velMax;
    }
    void setBehavior(int newBehav){
        behavior = newBehav;
    }
    
    void addBehavior(int mask) {
        behavior |= mask;
    }
    
    int behavior;
    
    ofVec3f position;
    ofVec3f velocity;
    
    ofVec3f angle;      
    ofVec3f angularSpeed;
    
    float drag;
    float stiffness;
    float mass;
};
//
//  ParticlePhysics.cpp
//  visuals002
//
//  Created by Rico on 19.01.16.
//
//

#include "ParticlePhysics.hpp"

ParticlePhysics::ParticlePhysics(){
    drag = 1.0;
    mass = 1.0;
    stiffness = ofRandom(0.001,0.003);
    behavior = STATUS_IDLE;
}
ParticlePhysics::~ParticlePhysics(){
    
}


void ParticlePhysics::move(ofVec3f velocity){
    velocity *= drag;
    position += velocity;
}

void ParticlePhysics::moveNoise(){
    float noiseScale = 0.02;
    float angle = ofNoise(position.x * noiseScale, position.y * noiseScale, position.z * noiseScale) * 2*TWO_PI;
    velocity = ofVec3f(cos(angle),sin(angle),0);
    position += velocity;
}

void ParticlePhysics::centralForce(){
    ofVec3f F = -position * stiffness;
    velocity += F;
    velocity *= drag;
    position += velocity;
}


void ParticlePhysics::accelerateToVelocity(ofVec3f a, float velMax){
    velocity += a;
    if (velocity.length() > velMax) {
        velocity = velocity.normalize()*velMax;
    }
}

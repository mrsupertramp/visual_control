//
//  ParticleSpecs.cpp
//  visuals002
//
//  Created by Rico on 19.01.16.
//
//
//
#include "ParticleSpecs.hpp"

ParticleSpecs::ParticleSpecs(){
    historyVisible = false;
    circleVisible = false;
    subparticleLineVisible = false;
    sphereVisible = false;
    historyLineWidth = 1.0;
    radius = 1.0;
    pastIndex = -1;
    
}

ParticleSpecs::~ParticleSpecs(){
    
}

void ParticleSpecs::setSpecs(ParticleSpecs& specs) {
    memcpy(this, &specs, sizeof(ParticleSpecs));
}


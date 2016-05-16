//
//  Particle.cpp
//  visuals002
//
//  Created by Rico on 08.12.15.
//
//

#include "Particle.hpp"

Particle::Particle(){
    //specs = new ParticleSpecs;
    subSpecs = new ParticleSpecs;
    //physics = new ParticlePhysics;
    subPhysics = new ParticlePhysics;
    
       // the light highlight of the material //
    
    icoSphere.setResolution(4);
}

Particle::~Particle(){
}

void Particle::generateParticle(ofVec3f pos, ofVec3f vel){
    
    subparticle.push_back(Particle());
    
    subparticle[subparticle.size()-1].setSpecs(*subSpecs);
    //memcpy(subparticle[subparticle.size()-1]->specs, subSpecs, sizeof(ParticleSpecs));

    subparticle[subparticle.size()-1].position = pos;
    subparticle[subparticle.size()-1].velocity = vel;
    
    subparticle[subparticle.size()-1].timeBorn = ofGetElapsedTimeMillis();
    
}

void Particle::eliminateParticle(int index){
    for (int i=subparticle[index].subparticle.size()-1 ; i>=0 ; --i){
        subparticle[index].subparticle.erase(subparticle[index].subparticle.begin()+i);
    }
    
    subparticle.erase(subparticle.begin() + index);
}

void Particle::generateWave(ofVec3f pos, ofVec3f velDir, float ampl, float stiff, float drag){
    generateParticle(pos, velDir);
    Particle* ptl = &(subparticle[subparticle.size()-1]);
    ptl->setBehavior(STATUS_MOVE);
    ptl->setHistoryVisible(false);
    ptl->stiffness = 0.03;
    ptl->lifeTime = 12000;
    int hisLineWidth = ptl->historyLineWidth;
    
    ptl->generateParticle(pos, ampl * ofVec3f(velDir.getRotated(90, ofVec3f(0,0,1))));
    
    ptl = &(subparticle[subparticle.size()-1].subparticle[subparticle[subparticle.size()-1].subparticle.size()-1]);
    ptl->setBehavior(STATUS_CENTRALFORCE);
    ptl->setHistoryVisible(true);
    ptl->setCircleVisible(true);
    ptl->pastIndex = -1;
    ptl->stiffness = stiff;
    ptl->drag = drag;
    ptl->historyLineWidth = 20;
    
}

void Particle::update(ofVec3f posParent, ofVec3f velParent){
    
    if (behavior & STATUS_MOVE) {
        move(velocity);
    }
    if (behavior & STATUS_CENTRALFORCE) {
        centralForce();
    }
    if (behavior & STATUS_GRAVITATION) {
        subparticleGravitation();
    }
    
    parentPosition = posParent;
    parentVelocity = velParent;
    
    if (saveHistoryEnabled) {
        saveHistory();
    }
    
    for (int i=subparticle.size()-1 ; i>=0 ; --i){
        
        if (subparticle[i].getTimeAlive() > subparticle[i].lifeTime && subparticle[i].lifeTime > 0) {
            eliminateParticle(i);
        } else {
            subparticle[i].update(position, velocity);
        }
    }

}

void Particle::update(){
    update(ofVec3f(0,0,0), ofVec3f(0,0,0));
}

void Particle::draw(){
    material.begin();
    
    if (historyVisible) {
        drawHistoryLine();
    }
    if (pastIndex >= 0) {
        drawPastCircle();
    }
    if (circleVisible) {
        drawCircle();
    }
    if (sphereVisible) {
        drawSphere();
    }
    if (subparticleLineVisible){
        drawSubparticleLine();
    }
    material.end();
    for (int i=0 ; i<subparticle.size() ; ++i){
        subparticle[i].draw();
    }
}

void Particle::saveHistory(){
    
    if (ofGetElapsedTimeMillis() - tLastHistorySave > saveHistoryIntervall) {
        posHistory.push_back(position + parentPosition);
        velHistory.push_back(velocity);
        if (posHistory.size() > historyMaxSize) {
            posHistory.erase(posHistory.begin());
            velHistory.erase(velHistory.begin());
        }
        tLastHistorySave = ofGetElapsedTimeMillis();
    }
}


void Particle::subparticleGravitation(){
    vector <ofVec3f> force;
    force.assign(subparticle.size(), ofVec3f(0,0,0));
    for (int i=0 ; i<subparticle.size() ; ++i){
        ofVec3f _force;
        for (int j=0 ; j<subparticle.size() ; ++j) {
            ofVec3f _r = subparticle[i].position - subparticle[j].position;
            if (i != j) {
                _force += subparticle[j].mass *
                _r.normalize() /
                abs(_r.length() * _r.length());
            }
            
        }
        force[i] = -0.0001 * subparticle[i].mass * _force;
    }
    for (int i=0 ; i<force.size() ; ++i){
        subparticle[i].velocity += force[i]/subparticle[i].mass;
        subparticle[i].position += subparticle[i].velocity;
    }
}


void Particle::setSubparticleStatus(int newBehavior){
    for (int i=0 ; i<subparticle.size() ; ++i){
        subparticle[i].setBehavior(newBehavior);
    }
}

void Particle::drawCircle(){
    
    ofCircle(position + parentPosition, radius);
}

void Particle::drawWireFrameSphere(){
    icoSphere.setPosition(position + parentPosition);
    icoSphere.setRadius(radius);
    icoSphere.drawWireframe();
}

void Particle::drawSphere(){
    icoSphere.setPosition(position + parentPosition);
    icoSphere.setRadius(radius);
    icoSphere.draw();
}

void Particle::drawSubparticleLine(){

    ofPath path;
    
    if (subparticle.size()) {
        path.moveTo(subparticle[0].position + position);

        for (int i=1 ; i<subparticle.size() ; ++i){
            path.curveTo(subparticle[i].position + position);
        }
        path.close();
        path.setFilled(false);
        path.setStrokeColor(ofColor(0));
        path.setStrokeWidth(subparticleLineWidth);
        
        path.draw();
    }
    
}
void Particle::drawSubparticleMesh(){
    
    ofPath path;
    
    if (subparticle.size()) {
        path.moveTo(subparticle[0].position + position);
        
        for (int i=1 ; i<subparticle.size() ; ++i){
            path.curveTo(subparticle[i].position + position);
        }
        path.close();
        path.setFilled(true);
        path.setStrokeColor(ofColor(0));
        path.setStrokeWidth(subparticleLineWidth);
        subparticleTessellation = path.getTessellation();
        subparticleTessellation.draw();
    }
    
}

void Particle::drawHistoryLine(){
    
    //als mesh berechnen, zu jedem punkt in der history werden zwei punkte senkrecht zum vecHistory berechnet
    ofVboMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    for( unsigned int i = 1; i < posHistory.size(); i++ ){
        ofVec3f thisPoint = posHistory[ i - 1 ];
        ofVec3f nextPoint = posHistory[ i ];
        ofVec3f direction = ( nextPoint - thisPoint );
        float distance = direction.length();
        ofVec3f unitDirection = direction.normalized();
        
        ofVec3f toTheLeft = unitDirection.getRotated( 90, ofVec3f( 0, 0, 1 ) );
        ofVec3f toTheRight = unitDirection.getRotated( -90, ofVec3f( 0, 0, 1 ) );
        
        ofVec3f leftPoint = thisPoint + toTheLeft * historyLineWidth;
        ofVec3f rightPoint = thisPoint + toTheRight * historyLineWidth;
        ofFloatColor fcolor = ofColor(220,ofMap(i,0,posHistory.size(),80,255));
        mesh.addColor( fcolor );
        mesh.addVertex( ofVec3f( leftPoint.x, leftPoint.y, leftPoint.z ) );
        mesh.addColor( fcolor );
        mesh.addVertex( ofVec3f( rightPoint.x, rightPoint.y, rightPoint.z ) );
    }
    mesh.draw();
}

    /*
    ofPath path;
    
    path.moveTo(posHistory[0]);
    for (int i=1 ; i<posHistory.size() ; ++i){
        path.lineTo(posHistory[i]);
    }
    //path.close();
    path.setFilled(false);
    path.setStrokeColor(0);
    path.setStrokeWidth(specs->historyLineWidth);
    path.draw();
    for (int i=0 ; i<subparticle.size() ; ++i){
        subparticle[i].drawHistoryLine();
    }
     */


void Particle::drawPastCircle(){
    //ofCircle(posHistory[pastIndex], 10);
}
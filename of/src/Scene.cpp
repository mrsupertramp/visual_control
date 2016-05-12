#include "Scene.h"

Scene::Scene(){
	

}

void Scene::draw(){
	ofBackground(0,0,0);
	ofCircle(ofVec3f(30,30,0), 30);
}

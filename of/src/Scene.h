/* Created by Enrico Steinfeld

Container für finale Bildausgabe eines Moduls (Partikel, Mandala...)
*/


#include "ofMain.h"

#pragma once

class Scene{
	public:
	
	Scene();
	
	void draw();
	void loop();
	
	//container für vergangene bilder
	
	int countFrames; 

};

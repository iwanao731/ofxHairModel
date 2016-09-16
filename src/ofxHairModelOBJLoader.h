#ifndef _OFX_HAIR_MODEL_OBJ_LOADER_
#define _OFX_HAIR_MODEL_OBJ_LOADER_

#include "ofMain.h"
#include "ofxHairModel.h"
#include "ofxHEMesh.h"

class ofxHairModelOBJLoader
{
public:
	bool loadModel(const string filename);
	void addModel(ofxHairModel &model);

private:
	ofxHEMesh hem;

};

#endif
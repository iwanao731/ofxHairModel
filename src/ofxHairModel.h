#ifndef _OFX_HAIR_MODEL_
#define _OFX_HAIR_MODEL_

#include "ofMain.h"
#include "ofxHairStrand.h"
#include "ofxHairParticle.h"

class ofxRenderParticle;

class ofxHairModel
{
public:

	ofxHairModel();
	~ofxHairModel();
	std::vector<ofxHairStrand> strands;
	vector<ofxRenderParticle> render_particles;
	vector<int> indices;

	void addHairStrand(const ofVec3f position, const ofVec3f normal, const float length, const int resolution);
	bool loadHairModel(string filename);
	bool loadHairModelAsText(string filename);
	bool loadHairModelUSC(string filename);

	bool exportHairModel(string filename);
	bool exportHairModelAsText(string filename);

	int getNumParticles() { return m_numParticles; };
	int getNumStrand() { return m_numStrands; }

	bool isExistence();

private:
	int m_numStrands;
	int m_numParticles;
};

class ofxRenderParticle
{
public:
	GLfloat r, g, b, a;
	GLfloat nx, ny, nz;
	GLfloat x, y, z;
};

#endif
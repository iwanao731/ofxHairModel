#ifndef _OFX_HAIR_STRAND_
#define _OFX_HAIR_STRAND_

#include "ofMain.h"
#include "ofxHairParticle.h"

struct interpolate
{
	float s, t, u;
	int idx[3];
};

class ofxHairStrand
{
public:
	int m_resolution;
	interpolate root_ratio;
	std::vector<float> m_length;
	std::vector<ofxHairParticle> m_particles;

	void setup(const unsigned int num, const float length, const ofVec3f position, const ofVec3f normal);
	void setDiableParticle(int index);
	int getResolution() { return m_resolution; }
	float getLength(int index) { return m_length[index]; }
	bool bGuideHair;
};

#endif
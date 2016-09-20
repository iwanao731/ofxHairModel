#ifndef _OFX_HAIR_STRAND_
#define _OFX_HAIR_STRAND_

#include "ofMain.h"
#include "ofxHairParticle.h"

struct interpolate
{
	float s, t, u;
	int idx[3];
};

enum HairType {
	NORMAL_HAIR = 0,
	GUIDE_HAIR = 1,
};

class ofxHairStrand
{
public:
	std::vector<ofxHairParticle> m_particles;

	// fundamental function
	void setup(const unsigned int num, const float length, const ofVec3f position, const ofVec3f normal);

	// set function
	void setDiableParticle(int index);
	void setResolution(const int resolution);
	void setHairType(const HairType type) { m_hairType = type; }
	void setRootTriRatio_Idx(int idx1, int idx2, int idx3);
	void setRootTriRatio_S(float s) { root_ratio.s = s; }
	void setRootTriRatio_T(float t) { root_ratio.t = t; }
	void setRootTriRatio_U(float u) { root_ratio.u = u; }
	void setLength(const int index, float length) { m_length[index] = length; }

	// get function
	int getResolution() { return m_resolution; }
	int getRootTriRatio_Idx(int number) { return root_ratio.idx[number]; }
	float getRootTriRatio_S() { return root_ratio.s; }
	float getRootTriRatio_T() { return root_ratio.t; }
	float getRootTriRatio_U() { return root_ratio.u; }
	float getLength(int index) { return m_length[index]; }
	HairType getHairType() { return m_hairType; }

private:
	int m_resolution;
	HairType m_hairType;
	interpolate root_ratio;
	std::vector<float> m_length;
};


#endif
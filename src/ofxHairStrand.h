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
	int getResolution()			{ return m_resolution; }
	int getRootTriRatio_Idx(int number) { return root_ratio.idx[number]; }
	float getRootTriRatio_S()	{ return root_ratio.s; }
	float getRootTriRatio_T()	{ return root_ratio.t; }
	float getRootTriRatio_U()	{ return root_ratio.u; }
	float getLength(int index)	{ return m_length[index]; }
	HairType getHairType()		{ return m_hairType; }

	// particle information
	void setParticle(int index, ofxHairParticle p) { m_particles[index] = p; }
	void setPosition(int index, ofVec3f pos) { m_particles[index].position = pos; }
	void setPosition0(int index, ofVec3f pos) { m_particles[index].position0 = pos; }
	void setPositionTemp(int index, ofVec3f pos) { m_particles[index].tmp_position = pos; }
	void setColor(int index, ofColor col) { m_particles[index].color = col; }
	void setDelta(int index, ofVec3f d) { m_particles[index].d = d; }
	void setMass(int index, float m) { m_particles[index].mass = m; m_particles[index].inv_mass = 1.0f/m; }

	ofxHairParticle getParticle(int index) { return m_particles[index]; }
	vector<ofxHairParticle> getParticles() { return m_particles; }
	ofVec3f getPosition(int index) { return m_particles[index].position; }
	ofVec3f getPosition0(int index) { return m_particles[index].position0; }
	ofVec3f getPositionTemp(int index) { return m_particles[index].tmp_position; }
	float getMass(int index) { return m_particles[index].mass; }
	ofVec3f getDelta(int index) { return m_particles[index].d; }
	ofColor getColor(int index) { return m_particles[index].color; }

private:
	int m_resolution;
	HairType m_hairType;
	interpolate root_ratio;
	std::vector<float> m_length;
	std::vector<ofxHairParticle> m_particles;
};


#endif
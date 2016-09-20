#include "ofxHairStrand.h"

void ofxHairStrand::setup(const unsigned int num, const float length, const ofVec3f position, const ofVec3f normal)
{
	m_resolution = num;
	m_length.resize(num);

	for (int i = 0; i<m_resolution; i++) {
		float mass = 1.0;
		m_length[i] = length;
		ofPoint pos = position + i * m_length[i] * normal.normalized();
		ofxHairParticle p(pos, mass);
		m_particles.push_back(p);
	}
}

void ofxHairStrand::setResolution(const int resolution)
{
	m_resolution = resolution;
	m_length.resize(m_resolution);
}

void ofxHairStrand::setDiableParticle(int index)
{
	m_particles[index].enabled = false;
}

void ofxHairStrand::setRootTriRatio_Idx(int idx1, int idx2, int idx3) {
	root_ratio.idx[0] = idx1;
	root_ratio.idx[1] = idx2;
	root_ratio.idx[2] = idx3;
}
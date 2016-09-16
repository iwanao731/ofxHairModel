#include "ofxHairParticle.h"

ofxHairParticle::ofxHairParticle()
	: mass(1.0), inv_mass(1.0 / mass), enabled(true)
{
}

ofxHairParticle::ofxHairParticle(ofVec3f p, float m)
	: position(p), tmp_position(p), enabled(true)
{
	if (m < 0.001) {
		m = 0.001;
	}

	mass = m;
	inv_mass = 1.0 / mass;

	velocity = ofVec3f::zero();
}
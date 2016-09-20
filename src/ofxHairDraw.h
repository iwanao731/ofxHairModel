#ifndef _OFX_HAIR_DRAW_
#define _OFX_HAIR_DRAW_

#include "ofMain.h"
#include "ofxHairModel.h"

enum EHairColor;
enum EHairParticle;
enum EHairGuide;
enum EHairEdge;
enum EHairNormal;

class ofxHairDraw
{
public:
	ofxHairDraw(ofxHairModel &model);
	~ofxHairDraw();
	void init(EHairColor bCol, EHairParticle bParticle, EHairEdge bEdge, EHairNormal bNormal, EHairGuide bGuide);
	void update();
	void draw();

	void setHairModel(ofxHairModel &model);
	ofxHairDraw& setDrawHairColor(bool v);
	ofxHairDraw& setDrawHairParticles(bool v);
	ofxHairDraw& setDrawHairEdges(bool v);
	ofxHairDraw& setDrawHairNormal(bool v);
	ofxHairDraw& setDrawHairGuide(bool v);

	void updatePosition(ofxHairModel model);

private:
	GLuint buffers;   // vert+normal+texcord, index

	ofxHairModel& m_model;
	bool bDrawColor;
	bool bDrawNode;
	bool bDrawEdge;
	bool bDrawNormalHair;
	bool bDrawGuideHair;
};

enum EHairColor {
	HAIR_COLOR_OFF = 0,
	HAIR_COLOR_ON = 1,
};

enum EHairParticle {
	HAIR_PARTICLE_OFF = 0,
	HAIR_PARTICLE_ON = 1,
};

enum EHairGuide {
	HAIR_GUIDE_OFF = 0,
	HAIR_GUIDE_ON = 1,
};

enum EHairEdge {
	HAIR_EDGE_OFF = 0,
	HAIR_EDGE_ON = 1,
};

enum EHairNormal {
	HAIR_NORMAL_OFF = 0,
	HAIR_NORMAL_ON = 1,
};
#endif
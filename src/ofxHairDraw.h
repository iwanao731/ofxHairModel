#ifndef _OFX_HAIR_DRAW_
#define _OFX_HAIR_DRAW_

#include "ofMain.h"
#include "ofxHairModel.h"

class ofxHairDraw
{
public:
	ofxHairDraw(ofxHairModel &model);
	~ofxHairDraw();
	void init();
	void update();
	void draw();

	ofxHairDraw& setDrawHairColor(bool v);
	ofxHairDraw& setDrawHairParticles(bool v);
	ofxHairDraw& setDrawHairEdges(bool v);
	ofxHairDraw& setDrawHairNormal(bool v);
	ofxHairDraw& setDrawHairGuide(bool v);

	void updatePosition(ofxHairModel model);

private:
	GLuint buffers;   // vert+normal+texcord, index

	ofxHairModel& m_model;
	bool bColor;
	bool bNode;
	bool bEdge;
	bool bNormalHair;
	bool bGuideHair;
};

#endif
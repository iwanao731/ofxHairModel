#include "ofxHairDraw.h"
#define BUFFER_OFFSET(bytes) ((GLubyte *)NULL + (bytes))

ofxHairDraw::ofxHairDraw(ofxHairModel &model)
	: m_model(model)
{
}

ofxHairDraw::~ofxHairDraw()
{
	glDeleteBuffers(1, &buffers);
}

void ofxHairDraw::init()
{
	glGenBuffers(1, &buffers);

	glBindBuffer(GL_ARRAY_BUFFER, buffers);
	glBufferData(GL_ARRAY_BUFFER, m_model.getNumParticles() * sizeof(ofxRenderParticle), &m_model.render_particles[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ofxHairDraw::update()
{
	glBindBuffer(GL_ARRAY_BUFFER, buffers);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_model.getNumParticles() * sizeof(ofxRenderParticle), &m_model.render_particles[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ofxHairDraw::draw()
{
	glPushClientAttrib(GL_ALL_ATTRIB_BITS);

	glBindBuffer(GL_ARRAY_BUFFER, buffers);

	glInterleavedArrays(GL_C4F_N3F_V3F, 0, BUFFER_OFFSET(0));

	for (int i = 0; i < m_model.strands.size(); i++) {
		int res = m_model.strands[i].getResolution();
		glDrawArrays(GL_LINE_STRIP, i*res, res);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glPopClientAttrib();
}

ofxHairDraw& ofxHairDraw::setDrawHairParticles(bool v)
{
	bNode = v;
	return *this;
}

ofxHairDraw& ofxHairDraw::setDrawHairEdges(bool v)
{
	bEdge = v;
	return *this;
}

ofxHairDraw& ofxHairDraw::setDrawHairColor(bool v)
{
	bColor = v;
	return *this;
}

ofxHairDraw& ofxHairDraw::setDrawHairNormal(bool v)
{
	bNormalHair = v;
	return *this;
}


ofxHairDraw& ofxHairDraw::setDrawHairGuide(bool v)
{
	bGuideHair = v;
	return *this;
}

void ofxHairDraw::updatePosition(ofxHairModel model)
{
	int i = 0;
	for (auto s : model.strands)
	{
		for (auto p : s.m_particles)
		{
			m_model.render_particles[i].x = p.position.x;
			m_model.render_particles[i].y = p.position.y;
			m_model.render_particles[i].z = p.position.z;
			i++;
		}
	}
}
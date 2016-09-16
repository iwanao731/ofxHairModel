#include "ofxHairModel.h"

void ofxHairModel::addHairStrand(const ofVec3f position, const ofVec3f normal, const float length, const int resolution)
{
	ofxHairStrand s;
	s.setup(resolution, length, position, normal);
	s.setDiableParticle(0); // stick on the hairline

	strands.push_back(s);
	m_numStrands = strands.size();

	ofColor c;
	c.setHsb(ofRandom(0, 255), 200, 255, 255);

	for (auto p : s.m_particles)
	{
		ofxRenderParticle rp;
		rp.x = p.position.x;
		rp.y = p.position.y;
		rp.z = p.position.z;
		rp.nx = 0.0;
		rp.ny = 1.0;
		rp.nz = 0.0;
		rp.r = (float)c.r / 255.f;
		rp.g = (float)c.g / 255.f;
		rp.b = (float)c.b / 255.f;
		rp.a = (float)c.a / 255.f;
		render_particles.push_back(rp);
	}
	m_numParticles += s.getResolution();
}


// This format is created by "A Reduced Model for Interactive Hairs", SIGGRAPH 2014
bool ofxHairModel::loadHairModel(string filename)
{
	strands.clear();

	ofFile file;
	file.open(filename, ofFile::ReadOnly, true);
	if (!file.exists()) {
		ofLogVerbose("ofxHairModel") << "loadHairModel(): model does not exist: \"" << filename << "\"";
		return false;
	}

	// int : total particle size
	file.read((char*)&m_numParticles, sizeof(m_numParticles));
	std::cout << "Number of particles : " << m_numParticles << std::endl;

	render_particles.resize(m_numParticles);

	// total particle size * float * 3: all particle positions
	for (int i = 0; i<m_numParticles; i++) {
		float pos[3];
		file.read((char*)&pos, sizeof(pos));
		render_particles[i].x = pos[0];
		render_particles[i].y = pos[1];
		render_particles[i].z = pos[2];
		render_particles[i].nx = 0.0;
		render_particles[i].nx = 1.0;
		render_particles[i].nx = 0.0;
	}

	// int : total strand size
	file.read((char*)&m_numStrands, sizeof(m_numStrands));
	std::cout << "Number of strands : " << m_numStrands << std::endl;
	strands.resize(m_numStrands);

	// total strand size * int : particle size for each strand (use this to get the offset in all particle positions)
	for (int i = 0; i<m_numStrands; i++) {
		int resolution;
		file.read((char*)&resolution, sizeof(resolution));
		strands[i].m_resolution = resolution;
		strands[i].m_length.resize(strands[i].m_resolution);
		strands[i].m_particles.resize(resolution);
	}

	file.close();

	int count = 0;
	for (int i = 0; i<strands.size(); i++) {

		// set random color
		ofColor c;
		c.setHsb(ofRandom(0, 255), 200, 255, 255);

		for (int j = 0; j<strands[i].m_resolution; j++) {
			ofVec3f pos(render_particles[count].x, render_particles[count].y, render_particles[count].z);
			ofxHairParticle p(pos, 1.0);
			p.position0 = p.position;
			p.posPrev = p.position;
			strands[i].m_particles[j] = p;

			render_particles[count].r = (float)c.r / 255.f;
			render_particles[count].g = (float)c.g / 255.f;
			render_particles[count].b = (float)c.b / 255.f;
			render_particles[count].a = (float)c.a / 255.f;

			if (j == 0) {
				strands[i].setDiableParticle(0);
			}
			else {
				strands[i].m_length[j - 1] = (strands[i].m_particles[j - 1].position - strands[i].m_particles[j].position).length();
			}
			count++;
		}
	}

	return true;
}


bool ofxHairModel::exportHairModel(string filename)
{
	std::cout << "exporting... " << std::endl;

	std::fstream fout;

	fout.open(filename, std::ios::out | std::ios::binary | ios::trunc);
	if (!fout.is_open()) {
		cout << "file open error" << endl;
		return false;
	}

	// int : total particle size
	fout.write((char*)&m_numParticles, sizeof(int));

	// total particle size * float * 3: all particle positions
	for (int i = 0; i<m_numStrands; i++) {
		for (int j = 0; j<strands[i].getResolution(); j++) {
			float pos[3];
			pos[0] = strands[i].m_particles[j].position[0];
			pos[1] = strands[i].m_particles[j].position[1];
			pos[2] = strands[i].m_particles[j].position[2];
			fout.write((char*)&pos, sizeof(pos));
		}
	}

	// int : total strand size
	fout.write((char*)&m_numStrands, sizeof(int));

	// total strand size * int : particle size for each strand (use this to get the offset in all particle positions)
	for (int i = 0; i<m_numStrands; i++) {
		int resolution = strands[i].getResolution();
		fout.write((char*)&resolution, sizeof(int));
	}

	fout.close();  //ファイルを閉じる
	std::cout << "saved as... '" << filename << "'" << std::endl;
	return true;
}


bool ofxHairModel::loadHairModelAsText(string filename)
{
	std::fstream file;
	char buf[16];

	file.open(filename, std::ios::in);
	if (!file.is_open()) {
		cout << "file open error" << endl;
		return false;
	}

	// int : total particle size
	file >> m_numParticles;
	std::cout << "Number of particles : " << m_numParticles << std::endl;

	ofxHairParticle *particles;
	particles = new ofxHairParticle[m_numParticles];

	// total particle size * float * 3: all particle positions
	for (int i = 0; i<m_numParticles; i++) {
		float pos[3];
		file >> pos[0] >> pos[1] >> pos[2];
		particles[i].position = ofVec3f(pos[0], pos[1], pos[2]);
		particles[i].tmp_position = ofVec3f(pos[0], pos[1], pos[2]);
		//std::cout << pos[0] << "," << pos[1] << "," << pos[2] << endl;
	}

	// int : total strand size
	file >> m_numStrands;
	std::cout << "Number of strands : " << m_numStrands << std::endl;
	strands.resize(m_numStrands);

	// total strand size * int : particle size for each strand (use this to get the offset in all particle positions)
	for (int i = 0; i<m_numStrands; i++) {
		int resolution;
		file >> resolution;
		strands[i].m_resolution = resolution;
		strands[i].m_length.resize(strands[i].m_resolution);
		strands[i].m_particles.resize(resolution);
	}

	file.close();

	int count = 0;
	for (int i = 0; i<strands.size(); i++) {

		// set random color
		ofColor c;
		c.setHsb(ofRandom(0, 255), 200, 255, 255);
		//c = ofColor((float)c.r/255, (float)c.g/255, (float)c.b/255);

		for (int j = 0; j<strands[i].m_resolution; j++) {
			strands[i].m_particles[j].position = particles[count].position;
			strands[i].m_particles[j].position0 = ofVec3f(particles[count].position.x, particles[count].position.y, particles[count].position.z);
			strands[i].m_particles[j].tmp_position = particles[count].tmp_position;
			strands[i].m_particles[j].color = c;

			indices.push_back(count);

			/* set mass */
			float SgRoot = 1.0;
			float SgTip = 0.5;
			float t = j / (float)strands[i].m_resolution;
			float Sg = (1.0f - t) * SgRoot + t * SgTip;
			strands[i].m_particles[j].mass = Sg;
			strands[i].m_particles[j].inv_mass = 1.0 / Sg;

			if (j == 0) {
				strands[i].setDiableParticle(0);
			}
			else {
				strands[i].m_length[j - 1] = (strands[i].m_particles[j - 1].position - strands[i].m_particles[j].position).length();
			}

			count++;
		}
	}

	return true;
}

bool ofxHairModel::exportHairModelAsText(string filename)
{
	std::cout << "exporting... " << std::endl;

	std::fstream fout;
	char buf[16];

	fout.open(filename, std::ios::out | ios::trunc);
	if (!fout.is_open()) {
		cout << "file open error" << endl;
		return false;
	}

	// int : total particle size
	fout << m_numParticles << endl;

	// total particle size * float * 3: all particle positions
	for (int i = 0; i<m_numStrands; i++) {
		for (int j = 0; j<strands[i].getResolution(); j++) {
			float pos[3];
			pos[0] = strands[i].m_particles[j].position[0];
			pos[1] = strands[i].m_particles[j].position[1];
			pos[2] = strands[i].m_particles[j].position[2];
			fout << pos[0] << "\t" << pos[1] << "\t" << pos[2] << endl;
		}
	}

	// int : total strand size
	fout << m_numStrands << endl;

	// total strand size * int : particle size for each strand (use this to get the offset in all particle positions)
	for (int i = 0; i<m_numStrands; i++) {
		int resolution = strands[i].getResolution();
		fout << resolution << endl;
	}

	fout.close();  //ファイルを閉じる
	std::cout << "saved as... '" << filename << "'" << std::endl;
	return true;
}
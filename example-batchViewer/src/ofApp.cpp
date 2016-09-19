#include "ofApp.h"
#include "ofxHEMeshDraw.h"

int frameCount = 0;
ofDirectory *hairDir;

//--------------------------------------------------------------
void ofApp::setup(){

	string hair_filepath = "../../../../../apps/hairSim/HairBatchViewer/bin/data/exp3";
	hairDir = new ofDirectory(hair_filepath);
	cout << hairDir->listDir() << endl;

	string mesh_filepath = "../../../../../apps/sharedData/model/sphere.obj";
	hem.loadOBJModel(mesh_filepath);

	initHem = hem;

	hairModel.loadHairModel(hairDir->getPath(frameCount));

	viewer = new ofxHairDraw(hairModel);
	viewer->setDrawHairColor(true);
	viewer->setDrawHairParticles(false);
	viewer->setDrawHairEdges(true);
	viewer->setDrawHairNormal(true);
	viewer->setDrawHairGuide(true);
	viewer->init();
}

//--------------------------------------------------------------
void ofApp::update(){

	ofxHairModel m;
	m.loadHairModel(hairDir->getPath(frameCount));
	viewer->updatePosition(m);
	viewer->update();

	frameCount++;
	if (hairDir->numFiles() <= frameCount)
		frameCount = 0;

	cout << frameCount << "/" << hairDir->size() << endl;
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	ofEnableDepthTest();

	cam.begin();

	ofPushMatrix();
	ofSetColor(255);
	hem.setTopologyDirty(true);
	ofxHEMeshDraw hedraw(hem);
	hedraw.setDrawEdges(true);
	hedraw.setDrawFaces(true);
	hedraw.draw(cam);

	viewer->draw();

	ofPopMatrix();
	cam.end();

	ofSetColor(255);
	ofDisableDepthTest();
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key)
	{
	case 'f':
		ofToggleFullscreen();
		break;
	case 'r':
		frameCount = 0;
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

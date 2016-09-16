#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	string hairname = "hair_example.data";
	string filename = "head_model.obj";

	hairModel.loadHairModel(hairname);
	mesh.loadOBJModel(filename);

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

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	ofEnableDepthTest();

	cam.begin();

	ofPushMatrix();
	ofTranslate(0, -500, 400);

	ofSetColor(255);
	mesh.setTopologyDirty(true);
	ofxHEMeshDraw hedraw(mesh);
	hedraw.setDrawEdges(true);
	hedraw.setDrawFaces(true);
	hedraw.draw(cam);

	viewer->draw();
	ofPopMatrix();

	cam.end();

	ofDisableDepthTest();
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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

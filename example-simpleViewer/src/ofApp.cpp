#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	string hairname = "strands00001.data"; // Hao Hair Model
	string filename = "head_model.obj";

	hairModel.loadHairModelUSC(hairname);
	//hairModel.loadHairModel(hairname);

	hairModel.exportHairModelAsText("exported_" + hairname);

	mesh.loadOBJModel(filename);

	if (hairModel.isExistence())
	{
		viewer = new ofxHairDraw(hairModel);
		viewer->init(EHairColor::HAIR_COLOR_ON, EHairParticle::HAIR_PARTICLE_OFF, EHairEdge::HAIR_EDGE_ON, EHairNormal::HAIR_NORMAL_ON, EHairGuide::HAIR_GUIDE_ON);
	}
	else {
		cout << "not existence" << endl;
	}
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

//--------------------------------------------------------------
void ofApp::processOpenFileSelection(ofFileDialogResult openFileResult) {

	ofLogVerbose("getName(): " + openFileResult.getName());
	ofLogVerbose("getPath(): " + openFileResult.getPath());

	cout << "reading >>> " << openFileResult.getPath() << endl;
	ofFile file(openFileResult.getPath());

	if (file.exists()) {
		//Limiting this example to one image so we delete previous ones
		ofLogVerbose("The file exists - now checking the type via file extension");
		string fileExtension = ofToUpper(file.getExtension());

		if (fileExtension == "DATA") {
			hairModel.loadHairModelUSC(openFileResult.getPath());
		}
	}
}

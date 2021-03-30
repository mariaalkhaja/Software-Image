#include "ofApp.h"

int x[300], y[300];
//--------------------------------------------------------------
void ofApp::setup() {
    gui.setup();

    gui.add(intSlider.setup("Number of Lines", 15, 1, 300));
    gui.add(intWidth.setup("Line Width", 2, 1, 50));
    gui.add(vec4Slider.setup("Line Color", ofVec4f(254, 200, 216, 100), ofVec4f(0, 0, 0, 0), ofVec4f(255, 255, 255, 255)));

    for (int i = 0; i <= 300; i++) {
        x[i] = ofRandom(800);
        y[i] = ofRandom(800);
    }
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
    for (int i = 0; i < intSlider; i++) {
        ofDrawLine(ofGetWidth() / 2, ofGetHeight() / 2, x[i], y[i]);
    }

    ofSetColor(vec4Slider->x, vec4Slider->y, vec4Slider->z, vec4Slider->w);
    ofSetLineWidth(intWidth);

    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofNoFill();
	ofSetBackgroundColor(0);
    font.load("terminal-grotesque_open.otf", 35);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
    float elapsedtime = ofGetElapsedTimef();
    elapsedtime = int(elapsedtime) % 45;
    int d = int(ofGetElapsedTimef()) % 360;
    int hypno = 16;

    if (elapsedtime < hypno) {
        ofSetColor(255, 0, 0, 255);
        for (int i = 0; i < 360; i += 10) {
            ofPushMatrix();
            ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
            ofRotateDeg((d * 2) - 90);
            ofRotateDeg(i);
            font.drawString("you", 90, 0);
            ofSetColor(255, 255, 255);
            ofPopMatrix();
        }
    }

    if (elapsedtime > 2 and elapsedtime < hypno) {
        ofSetColor(255, 0, 0, 200);
        for (int i = 0; i < 360; i += 10) {
            ofPushMatrix();
            ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
            ofRotateDeg((d * 3) + 45);
            ofRotateDeg(i);
            font.drawString("will", 150, 0);
            ofSetColor(255, 255, 255, 170);
            ofPopMatrix();
        }
    }
    
    if (elapsedtime > 4 and elapsedtime < hypno) {
        ofSetColor(255, 0, 0, 160);
        for (int i = 0; i < 360; i += 10) {
            ofPushMatrix();
            ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
            ofRotateDeg((d * 6));
            ofRotateDeg(i - 30);
            font.drawString("be", 210, 0);
            ofSetColor(255, 255, 255, 100);
            ofPopMatrix();
        }
    }
    
    if (elapsedtime > 6 and elapsedtime < hypno) {
        ofSetColor(255, 0, 0, 130);
        for (int i = 0; i < 360; i += 10) {
            ofPushMatrix();
            ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
            ofRotateDeg((d * 9) + 60);
            ofRotateDeg(i);
            font.drawString("hypnotized", 250, 0);
            ofSetColor(255, 255, 255, 66);
            ofPopMatrix();
        }
    }

    if (elapsedtime > hypno+2) {
        ofPushMatrix();
        ofSetColor(255, 255, 255, 255);
        int time = ofGetSystemTimeMillis() / 45;

        ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
        ofSetLineWidth(8);
        for (int i = 0; i < 400; i += 12) {
            ofDrawCircle(i, 0, 10);
            ofRotateDeg(time % 360);
        }
        ofPopMatrix();
    }
}




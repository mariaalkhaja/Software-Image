#include "ofApp.h"

int k = 0;
int zero = 0;
int one = 0;
int two = 0;
int three = 0;
int play = 0; 

//--------------------------------------------------------------
void ofApp::setup(){
	sound.setMultiPlay(true);   // multiple sounds can play  
	sound.load("phaser.wav");   // load sound
	sound.setVolume(0.4);       // set volume 
	sound.play();               // play sound 
	sound.setLoop(true);        // loop it
	dance.load("dance1.mp4");   // load video 
	
	// initialize fft 
	fft = new float[512]; 
	for (int i = 0; i < 512; i++) {
		fft[i] = 0;
	}

	
	ofBackground(0); // set background to black
	bands = 512;     // bands cannot go over fft 
	decay = 0.9;     // how fast or slow shapes are going in and out 
}

//--------------------------------------------------------------
void ofApp::update(){
	ofSoundUpdate(); // update the sound playing system:

	soundSpectrum = ofSoundGetSpectrum(bands); // get sound frequencies 

	// link decay with bands
	for (int i = 0; i < bands; i++) {
		fft[i] *= decay; 

		// if fft is less than sound spectrum
		if (fft[i] < soundSpectrum[i]) {
			fft[i] = soundSpectrum[i]; // set fft to sound specturm 
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	float elapsedtime = ofGetElapsedTimef(); // get float time system has been running
	int time = int(elapsedtime);  // time running in int 

	// if running for less than 9 secs 
	if (time < 9) {
		ofPushMatrix();
		ofTranslate(256, 256);

		// random color generator
		int r = ofRandom(0, 255);
		int g = ofRandom(0, 255);
		int b = ofRandom(0, 255);

		// draw polylines 
		for (int i = 0; i < k; i += 60) {
			ofPolyline polyline;

			for (int j = 0; j < bands; j++) {
				polyline.addVertex(j, i - fft[j] * 100.0);
			}
			polyline.draw();
		}

		// at each specified time add an additional polyline 
		if (time == 2 and zero == 0) {
			k += 60;             // increment k by 60 so that an additional polyline can be drawn (i<k)
			zero = 1;            // increment zero so the if statement only runs once
			ofSetColor(r, g, b); // change polylines to a randomly chosen color 
		}

		else if (time == 3 and one == 0) {
			k += 60;
			one = 1;
			ofSetColor(r, g, b);
		}

		else if (time == 5 and two == 0) {
			k += 60;
			two = 1;
			ofSetColor(r, g, b);
		}

		else if (time == 7 and three == 0) {
			k += 60;
			three = 1;
			ofSetColor(r, g, b);
		}

		ofPopMatrix();
	}

	// otherwise if running for less than 19 secs 
	else if (time < 19) {
		if (play == 0) {
			sound1.setMultiPlay(true);
			sound1.load("cold.wav"); // add another beat 
			sound1.setVolume(1.0);
			sound1.play();
			sound1.setLoop(true);
			play = 1;
		}

		ofBackground(17, 134, 164); // change background color 
		ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2); // translate to middle of screen 

		int ttime = ofGetSystemTimeMillis() / 45;
		ofNoFill();

		// draw 20 pentagons at the center
		for (int i = 0; i < 400; i += 20) {
			int r = ofRandom(0, 255);
			int g = ofRandom(0, 255);
			int b = ofRandom(0, 255);
			ofSetColor(r, g, b);
			ofSetCircleResolution(5);
			ofDrawCircle(0, 0, (fft[i] + 0.015) * 500.0); // size of pentagons changes with beat 
			ofRotateDeg(ttime % 360); // pentagons rotate in place 
		}

		// if more than 12 seconds passed
		if (time >= 12) {
			// draw 20 pentagones at screenwidth/4 to form a big circle
			for (int i = 0; i < 400; i += 20) {
				int r = ofRandom(0, 255);
				int g = ofRandom(0, 255);
				int b = ofRandom(0, 255);
				ofSetColor(r, g, b);
				ofSetCircleResolution(5);
				ofDrawCircle(ofGetWidth()/4, 0, (fft[i] + 0.015) * 500.0); // size changes with beat
				ofRotateDeg(ttime % 360);
			}
		}
	}

	// otherwise if running for less than 28 secs 
	else if (time < 28) {
		ofBackground(187, 143, 206);
		if (play == 1) {
			sound2.setMultiPlay(true);
			sound2.load("loop.wav");     // add new beat
			sound2.play();
			sound2.setLoop(true);
			sound3.setMultiPlay(true);
			sound3.load("drumloop.wav"); // add new beat 
			sound3.play();
			sound3.setLoop(true);
			play = 2;
		}
		
		ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
		int ttime = ofGetSystemTimeMillis() / 45;
		ofNoFill();
		// draw prentagons at i 
		for (int i = 0; i < 400; i += 20) {
			int r = ofRandom(0, 255);
			int g = ofRandom(0, 255);
			int b = ofRandom(0, 255);
			ofSetColor(r, g, b);
			ofDrawCircle(i, 0, (fft[i] + 0.015) * 500.0); // size changes with beat
			ofRotateDeg(ttime % 360); // move around screen 
		}
	}

	// otherwise if running for less than 60 secs 
	else if (time < 60) {
		ofBackground(187, 143, 206);
		if (play == 2) {
			sound4.setMultiPlay(true);
			sound4.load("dance.wav"); // add beat
			sound4.play();
			sound4.setLoop(true);
			dance.play(); // play video 
			play = 3;
		}
		
		ofFill();
		ofSetFrameRate(20);
		ofSetCircleResolution(10); 
		ofBackground(247, 220, 111);

		// for video width and height 
		for (int i = 0; i < dance.getWidth(); i += 16) {
			for (int j = 0; j < dance.getHeight(); j += 16) {

				ofColor white(255, 255, 255, 255); // set color white 
				ofColor color = dance.getPixels().getColor(i, j); // get video pixels color 

				int r = ofRandom(0, 255);
				int g = ofRandom(0, 255);
				int b = ofRandom(0, 255);
				
				// if pixels are white
				if (color == white) {
					ofSetColor(r, g, b); // set to randomly generated color
				}

				// otherwise keep color
				else 
					ofSetColor(color);

				float brightness = color.getBrightness(); // set brightness based on color brightness 
				float radius = ofMap(brightness, 0, 255, 0, 8); // set radius based on brightness remaped between 0-8

				ofDrawCircle(i, j, radius); // draw mosaic circles 
			}
		}
	}
}


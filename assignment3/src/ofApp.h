#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		ofImage cloud;
		ofImage door;
		ofImage red;
		ofImage dark;

		ofSoundPlayer sound;
		ofSoundPlayer sound1;
		ofSoundPlayer sound2;
		ofSoundPlayer sound3;
		ofSoundPlayer sound4;
		ofSoundPlayer sound5;
		ofSoundPlayer sound6;
		ofSoundPlayer sound7;
		ofSoundPlayer sound8;
		ofSoundPlayer sound9;
		ofSoundPlayer sound10;
		ofSoundPlayer sound11;
		ofSoundPlayer sound12;
		ofSoundPlayer sound13;
		ofSoundPlayer sound14;
		ofSoundPlayer sound15;
		ofSoundPlayer sound16;
		ofVideoPlayer dance;
		

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		int home;
		int mousex;
		int mousey;
		bool click;
		ofFbo fbo;
		ofPolyline polyline;
		ofPolyline polyline1;
		ofPolyline polyline2;
		ofColor color;
		

		float* fft;
		float* soundSpectrum;
		int bands;
		float decay;
		int trans;
};

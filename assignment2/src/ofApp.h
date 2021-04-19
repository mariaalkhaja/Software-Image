#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

	ofSoundPlayer sound;
	ofSoundPlayer sound1;
	ofSoundPlayer sound2;
	ofSoundPlayer sound3;
	ofSoundPlayer sound4;
	ofVideoPlayer dance;


	float* fft;
	float* soundSpectrum;
	int bands;
	float decay;
};

#include "ofApp.h"

int background = 0;
int play = 0;
int d = ofRandom(70, 100);
int u = ofRandom(0, 30);
int up = 0;
int bands = 512;


//--------------------------------------------------------------
void ofApp::setup() {
    home = 0;
    ofBackground(247, 220, 111);
    cloud.load("cloud.png");
    door.load("door.png");
    sound.setMultiPlay(true);
    sound.load("glitch.mp3");   // load sound
    sound1.setMultiPlay(true);
    sound1.load("start1.mp3");
    sound2.setMultiPlay(true);
    sound2.load("background.mp3");
    sound3.setMultiPlay(true);
    sound3.load("knock.mp3");
    sound4.setMultiPlay(true);
    sound4.load("enter.mp3");
    sound5.setMultiPlay(true);
    sound5.load("musical.mp3");
    sound6.setMultiPlay(true);
    sound6.load("vocal.mp3");
    sound7.setMultiPlay(true);
    sound7.load("dance.mp3");
    dance.load("dance1.mp4");
    sound8.setMultiPlay(true);
    sound8.load("cold.wav");
    red.load("red1.png");
    dark.load("dark.png");
    sound9.setMultiPlay(true);
    sound9.load("1.mp3");
    sound10.setMultiPlay(true);
    sound10.load("2.mp3");
    sound11.setMultiPlay(true);
    sound11.load("3.mp3");
    sound12.setMultiPlay(true);
    sound12.load("4.mp3");
    sound13.setMultiPlay(true);
    sound13.load("5.mp3");
    sound14.setMultiPlay(true);
    sound14.load("6.mp3");
    sound15.setMultiPlay(true);
    sound15.load("7.mp3");
    sound16.setMultiPlay(true);
    sound16.load("8.mp3");

    ofEnableSmoothing();
    fbo.allocate(ofGetScreenWidth(), ofGetScreenHeight());
    fbo.begin();
    ofClear(255);
    fbo.end();

    fft = new float[512];
    for (int i = 0; i < 512; i++) {
        fft[i] = 0;
    }


    bands = 512;     // bands cannot go over fft 
    decay = 0.9;
}

//--------------------------------------------------------------
void ofApp::update() {
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
void ofApp::draw() {
    ofSetLineWidth(1.0);
    float elapsedtime = ofGetElapsedTimef(); // get float time system has been running
    int time = int(elapsedtime);  // time running in int 
    //cout << time;

    if (time < 9) {
        if (play == 0) {
            sound.play();               // play sound
            play = 1;
        }
        for (int i = 0; i < ofGetHeight(); i++)
        {
            int r = ofRandom(0, 255);
            int g = ofRandom(0, 255);
            int b = ofRandom(0, 255);
            ofSetColor(r, g, b);
            ofDrawLine(0, i, ofGetWidth(), i);
        }
    }

    else if (time < 11) {
        for (int i = 0; i < 360; i += 10) {
            ofPushMatrix();
            ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
            ofRotateDeg(ofGetSystemTimeMillis() / 3);
            ofRotateDeg(i);
            ofDrawCircle(20, 0, 10);
            ofSetColor(255, 255, 255, i - 100);
            ofPopMatrix();
        }
        if (play == 1 && time == 9) {
            sound1.play();               // play sound
            play = 2;
        }
    }

    else {
        if (home == 0) {
            if (play == 2) {
                sound2.play();
                sound2.setLoop(true);
                ofBackground(247, 220, 111, 255);
                play = 3;
            }

            ofNoFill();

            for (int i = 0; i < ofGetScreenWidth(); i += 600) {
                cloud.draw(i - 20, 20);
                cloud.draw(i + 300, 120);
            }

            door.draw(1050, 340);
            door.draw(550, 340);
            door.draw(50, 340);

            if (mousey > 540 and mousey < 980 and mousex > 300 and mousex < 600) {
                if (play == 3) {
                    sound3.play();
                    play = 4;
                }
                if (click) {
                    home = 1;
                    sound4.play();
                }
            }

            else if (mousey > 540 and mousey < 980 and mousex > 800 and mousex < 1100) {
                if (play == 3) {
                    sound3.play();
                    play = 4;
                }
                if (click) {
                    home = 2;
                    sound4.play();
                }
            }
            else if (mousey > 540 and mousey < 980 and mousex > 1300 and mousex < 1600) {
                if (play == 3) {
                    sound3.play();
                    play = 4;
                }
                if (click) {
                    home = 3;
                }
            }
            else {
                play = 3;
            }
        }

        else if (home == 1) {
            if (play == 4) {
                sound5.play();
                sound6.play();
                sound6.setVolume(0.0);
                play = 5;
            }

            ofBackground(0);
            fbo.draw(0, 0);
        }

        else if (home == 2) {
            if (play == 4) {
                ofBackground(255, 255, 255, 255);
                sound8.setVolume(0.5);
                sound8.play();
                sound8.setLoop(true);
                play = 5;
            }

            int r = ofRandom(50, 255);
            int g = ofRandom(50, 255);
            int b = ofRandom(50, 255);
            int move = 0;
            ofBackground(r, g, b, 255);

            red.draw(150, 80);
            red.draw(550, 80);
            red.draw(950, 80);
            red.draw(1350, 80);
            red.draw(150, 480);
            red.draw(550, 480);
            red.draw(950, 480);
            red.draw(1350, 480);

            if (mousey > 80 and mousey < 480 and mousex > 150 and mousex < 550) {
                dark.draw(150, 80);
                if (move != 1) {
                    sound9.setVolume(1.0);
                    sound9.play();
                    move = 1;
                }
            }
            else if (mousey > 80 and mousey < 480 and mousex > 550 and mousex < 950) {
                dark.draw(550, 80);
                if (move != 2) {
                    sound10.setVolume(1.0);
                    sound10.play();
                    move = 2;
                }
            }
            else if (mousey > 80 and mousey < 480 and mousex > 950 and mousex < 1350) {
                dark.draw(950, 80);
                if (move != 3) {
                    sound11.setVolume(1.0);
                    sound11.play();
                    move = 3;
                }
            }
            else if (mousey > 80 and mousey < 480 and mousex > 1350 and mousex < 1750) {
                dark.draw(1350, 80);
                if (move != 4) {
                    sound12.setVolume(1.0);
                    sound12.play();
                    move = 4;
                }
            }
            else if (mousey > 480 and mousey < 880 and mousex > 150 and mousex < 550) {
                dark.draw(150, 480);
                if (move != 5) {
                    sound13.setVolume(1.0);
                    sound13.play();
                    move = 5;
                }
            }
            else if (mousey > 480 and mousey < 880 and mousex > 550 and mousex < 950) {
                dark.draw(550, 480);
                if (move != 6) {
                    sound14.setVolume(1.0);
                    sound14.play();
                    move = 6;
                }
            }
            else if (mousey > 480 and mousey < 880 and mousex > 950 and mousex < 1350) {
                dark.draw(950, 480);
                if (move != 7) {
                    sound15.setVolume(1.0);
                    sound15.play();
                    move = 7;
                }
            }
            else if (mousey > 480 and mousey < 880 and mousex > 1350 and mousex < 1750) {
                dark.draw(1350, 480);
                if (move != 8) {
                    sound16.setVolume(1.0);
                    sound16.play();
                    move = 8;
                }
            }

        }

        else if (home == 3) {
            if (play == 4) {
                ofBackground(128, 0, 0, 255);
                dance.play();
                sound7.setVolume(1.0);
                sound7.play();
                play = 5;
            }

            ofPushMatrix();
            ofFill();
            ofSetFrameRate(20);
            ofSetCircleResolution(10);


            ofTranslate(300, 150);
            // for video width and height 
            for (int i = 0; i < dance.getWidth(); i += 13) {
                for (int j = 0; j < dance.getHeight(); j += 13) {

                    color = dance.getPixels().getColor(i, j); // get video pixels color 
                    ofColor white = (255, 255, 255, 255);


                    // if pixels are white
                    if (color == white) {
                        ofSetColor(255, 255, 210, 255); // set to light yellow
                    }

                    // otherwise keep color
                    else
                        ofSetColor(color);

                    float brightness = color.getBrightness(); // set brightness based on color brightness 
                    float radius = ofMap(brightness, 0, 255, 0, 6); // set radius based on brightness remaped between 0-8

                    ofDrawCircle(i, j, radius); // draw mosaic circles 
                }
            }

            ofSetCircleResolution(5);

            for (int i = dance.getWidth(); i < ofGetScreenWidth(); i += 21) {
                for (int j = -150; j < ofGetScreenHeight(); j += 21) {
                    ofDrawCircle(i, j, 10);
                    ofDrawCircle(dance.getWidth() - i, j, 10);
                    ofSetColor(255, 255, 210, 170);
                }
            }
            for (int i = dance.getHeight(); i < ofGetScreenHeight(); i += 21) {
                for (int j = -350; j < ofGetScreenWidth(); j += 21) {
                    ofDrawCircle(j, i, 10);
                    ofDrawCircle(j, dance.getHeight() - i, 10);
                    ofSetColor(160, 0, 0, 190);
                }
            }
            ofPopMatrix();
            ofSetColor(210, 210, 210, 255);
        }
    }
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (home == 1 and key == ' ') {
        fbo.begin();
        ofClear(255);
        fbo.end();
    }
    if (key == 'b') {
        home = 0;
        ofSoundStopAll();
        play = 2;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}


//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    mousex = x;
    mousey = y;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if (home == 1) {
        fbo.begin();
        ofSetLineWidth(6);
        int r = ofRandom(0, 255);
        int g = ofRandom(0, 255);
        int b = ofRandom(0, 255);
        ofSetColor(r, g, b, 255);
        polyline.addVertex(ofPoint(x, y));
        polyline.draw();
        ofSetLineWidth(4);
        ofSetColor(r, b, g, 190);
        polyline1.addVertex(ofPoint(x+8, y-8));
        polyline1.draw();
        ofSetLineWidth(2);
        ofSetColor(b, g, r, 150);
        for (int j = 0; j < bands; j++) {
            polyline2.addVertex(ofPoint(x + 16, y - 16 - fft[j] * 45.0));
        }
        polyline2.draw();
        
        sound6.setVolume(1.0);
        fbo.end();
    }
    sound6.setVolume(1.0);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    click = true;

    if (home == 1) {
        fbo.begin();
        polyline.clear();
        polyline1.clear();
        polyline2.clear();
        fbo.end();
    }
    sound6.setVolume(0.2);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    click = false;
    sound6.setVolume(0.2);
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

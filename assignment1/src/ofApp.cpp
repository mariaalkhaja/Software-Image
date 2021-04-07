#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	gui.setup();
	
	gui.add(intNoise.setup("Noise", .50, .30, .70)); // control how visible image is 
	gui.add(intPuzzle.setup("Puzzle", 1, 1, 300)); // control rising and falling of mesh
	gui.add(intImage.setup("Image", 1, 1, 4)); // change image on screen
	gui.add(vec3Slider.setup("Background Color", ofVec3f(254, 200, 216), 
		ofVec3f(0, 0, 0), ofVec3f(255, 255, 255))); // change background color

	ofSetLineWidth(2);
	ofEnableDepthTest();
	
	image.load("v.jpg"); // load image
	image.resize(1280, 720); // resize 
	image.allocate(1280, 720, OF_IMAGE_COLOR);
	this->cap_size = cv::Size(1280, 720);

	this->frame = cv::Mat(cv::Size(this->image.getWidth(), this->image.getHeight()), CV_MAKETYPE(CV_8UC3, this->image.getPixels().getNumChannels()), this->image.getPixels().getData(), 0);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	cv::Mat src;
	this->cap >> src;
	if (src.empty()) {

		this->cap.set(cv::CAP_PROP_POS_FRAMES, 0);
		return;
	}

	cv::cvtColor(src, src, cv::COLOR_BGR2RGB);
	cv::resize(src, this->frame, this->cap_size);
	cv::flip(this->frame, this->frame, 0);

	this->image.update();
}

//--------------------------------------------------------------
void ofApp::draw() {

	// update image based in intImage slider value 
	if (intImage == 1) {
		image.load("v.jpg");
	}
	else if (intImage == 2) {
		image.load("pop.jpg");
	}
	else if (intImage == 3) {
		image.load("hand.jpg");
	}
	else if (intImage == 4) {
		image.load("sunset.jpg");
	}

    // resize image 
	image.resize(1280, 720);
	image.allocate(1280, 720, OF_IMAGE_COLOR);
	
	
	ofSetBackgroundColor(vec3Slider->x, vec3Slider->y, vec3Slider->z); // set background color based on slider value 
	ofDisableDepthTest(); // disable depth test so gui can be drawn
	gui.draw(); // draw gui
	ofEnableDepthTest(); // re-enable depth test 

	this->cam.begin();
	ofTranslate(-400, -200, -700); // traslate image to this position on screen 

	vector<ofMesh> mesh_list;

	// for each frame of the image 
	for (int x = 0; x < 1280; x += 40) {
		for (int y = 0; y < 720; y += 40) {

			// calculates a 2D noise value between 0.0 and 1.0
			auto noise_value = ofNoise(x * 0.005, y * 0.001 + ofGetFrameNum() * 0.005);
			
			// generate two mesh of vertices 
			ofMesh mesh_1, mesh_2;

			// add new vertecies to mesh 1
			mesh_1.addVertex(glm::vec3(x, y, 0));
			mesh_1.addVertex(glm::vec3(x + 40, y, 0));
			mesh_1.addVertex(glm::vec3(x + 40, y + 40, 0));

			// add vector representing texture coordinates 
			mesh_1.addTexCoord(glm::vec3(x, y, 0));
			mesh_1.addTexCoord(glm::vec3(x + 40, y, 0));
			mesh_1.addTexCoord(glm::vec3(x + 40, y + 40, 0));

			// add new vertecies to mesh 1
			mesh_2.addVertex(glm::vec3(x, y + 40, 0));
			mesh_2.addVertex(glm::vec3(x + 40, y + 40, 0));
			mesh_2.addVertex(glm::vec3(x, y, 0));

			// add vector representing texture coordinates 
			mesh_2.addTexCoord(glm::vec3(x, y + 40, 0));
			mesh_2.addTexCoord(glm::vec3(x + 40, y + 40, 0));
			mesh_2.addTexCoord(glm::vec3(x, y, 0));

			// push into list 
			mesh_list.push_back(mesh_1);
			mesh_list.push_back(mesh_2);
		}
	}
	
	for (auto& mesh : mesh_list) {
			
			// rotation of triangles 
			auto rotate = glm::vec3(ofRandom(360), ofRandom(360), ofRandom(360));

			auto avg = (mesh.getVertex(0) + mesh.getVertex(1) + mesh.getVertex(2)) / 3;
			mesh.setVertex(0, mesh.getVertex(0) - avg);
			mesh.setVertex(1, mesh.getVertex(1) - avg);
			mesh.setVertex(2, mesh.getVertex(2) - avg);

			// noise generated for frames
			auto noise_value = ofNoise(glm::vec4(avg * 0.001, intPuzzle * 0.005));
			
			// bottom screen
			if (noise_value < intNoise) {
				avg += glm::vec3(0, 0, -250);
				rotate = glm::vec3(); // rotates puzzle back
			}

			// triangles between both screens (rising and falling)
			else if (noise_value < 0.52) {
				avg += glm::vec3(0, 0, ofMap(noise_value, 0.50, 0.52, -250, 250));
			}

			// top screen 
			else {
				avg += glm::vec3(0, 0, 250);
			}

			ofPushMatrix();
			ofTranslate(avg);
			ofRotateZ(rotate.z);
			ofRotateY(rotate.y);
			ofRotateX(rotate.x);

			ofSetColor(255);
			this->image.bind();
			mesh.draw();
			this->image.unbind();

			if (glm::length(rotate) > 0) {
				ofSetColor(39);
				mesh.drawWireframe();
			}

			ofPopMatrix();
		}
	

	ofNoFill();
	ofSetColor(200); // frame color 
	ofDrawRectangle(glm::vec3(0, 0, -250), 1280, 720); // frame for lower screen
	ofDrawRectangle(glm::vec3(0, 0, 250), 1280, 720);  // frame for upper screen 
	this->cam.end();
}


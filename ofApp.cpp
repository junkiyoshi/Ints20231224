#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofNoFill();

	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	if (ofGetFrameNum() % 50 < 15) {

		this->noise_value += ofMap(ofGetFrameNum() % 50, 0, 15, 0.1, 0);
	}

	ofColor color;
	for (int i = 0; i < 200; i++) {

		this->location_list.push_back(glm::vec2(ofRandom(-360, 360), ofRandom(-360, 360)));
		this->life_list.push_back(0);
	}

	for (int i = this->location_list.size() - 1; i >= 0; i--) {

		if (abs(this->location_list[i].x) > 460 || abs(this->location_list[i].y) > 460) {

			this->location_list.erase(this->location_list.begin() + i);
			this->life_list.erase(this->life_list.begin() + i);
		}
	}

	for (int i = 0; i < this->location_list.size(); i++) {

		auto deg = ofMap(ofNoise(this->location_list[i].x * 0.005, this->location_list[i].y * 0.005, this->noise_value), 0, 1, -360, 360);
		auto next = this->location_list[i] + glm::vec2(5 * cos(deg * DEG_TO_RAD), 5 * sin(deg * DEG_TO_RAD));
		this->location_list[i] = next;
		this->life_list[i] += 1;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	ofSetColor(ofColor(255, 64));
	for (int i = 0; i < this->location_list.size(); i++) {

		auto next = this->location_list[i];

		ofBeginShape();
		for (int k = 0; k < 25; k++) {

			auto deg = ofMap(ofNoise(next.x * 0.005, next.y * 0.005, this->noise_value), 0, 1, -360, 360);
			next = next + glm::vec2(5 * cos(deg * DEG_TO_RAD), 5 * sin(deg * DEG_TO_RAD));

			ofVertex(next);
		}
		ofEndShape();
	}

	/*
	int start = 75;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}


//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
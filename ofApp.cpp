#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(1.5);
	ofEnableDepthTest();

	ofTrueTypeFont font;
	font.loadFont("fonts/Kazesawa-Bold.ttf", 40, true, true, true);

	string word = "PULL";

	this->word_size = glm::vec2(font.stringWidth(word), font.stringHeight(word));
	this->path_list = font.getStringAsPoints(word, true, false);
}
//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(90);

	for (int x = -300; x <= 300; x += this->word_size.x * 1.1) {

		for (int y = -300; y <= 300; y += this->word_size.y * 1.1) {

			for (int path_index = 0; path_index < this->path_list.size(); path_index++) {

				auto outline = path_list[path_index].getOutline();

				ofSetColor(39);
				ofFill();
				ofBeginShape();
				for (int line_index = 0; line_index < outline.size(); line_index++) {

					if (line_index != 0) { ofNextContour(true); }

					auto vertices = outline[line_index].getVertices();
					for (int i = 0; i < vertices.size(); i++) {

						auto location = vertices[i] + glm::vec2(x, y);
						auto noise_value = ofNoise(glm::vec4(location * 0.0025, ofGetFrameNum() * 0.01));
						auto z = 0;
						if (noise_value < 0.25) { z = ofMap(noise_value, 0, 0.25, -350, 0); }
						if (noise_value > 0.75) { z = ofMap(noise_value, 0.75, 1, 0, 350); }
						ofVertex(location + glm::vec3(0, 0, z));
					}
				}
				ofEndShape(true);

				ofSetColor(239);
				ofNoFill();
				ofBeginShape();
				for (int line_index = 0; line_index < outline.size(); line_index++) {

					if (line_index != 0) { ofNextContour(true); }

					auto vertices = outline[line_index].getVertices();
					for (int i = 0; i < vertices.size(); i++) {

						auto location = vertices[i] + glm::vec2(x, y);
						auto noise_value = ofNoise(glm::vec4(location * 0.0025, ofGetFrameNum() * 0.01));
						auto z = 0;
						if (noise_value < 0.25) { z = ofMap(noise_value, 0, 0.25, -350, 0); }
						if (noise_value > 0.75) { z = ofMap(noise_value, 0.75, 1, 0, 350); }
						ofVertex(location + glm::vec3(0, 0, z));
					}
				}
				ofEndShape(true);
			}
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
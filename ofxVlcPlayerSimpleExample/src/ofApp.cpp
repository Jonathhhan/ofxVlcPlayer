#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofDisableArbTex();
	cam.setPosition(0, 0, 200);
	projectM.load();
	projectM.setWindowSize(1024, 1024);
	ofSetWindowTitle("ofxVlcPlayerSimpleExample");
	ofSetFrameRate(60);

	soundStream.printDeviceList();
	ofSoundStreamSettings settings;
	auto devices = soundStream.getDeviceList();
	settings.setOutDevice(devices[2]);
	settings.setOutListener(this);
	// Change the sample rate to the rate and output channels to the channel number of the file that you want to play!
	settings.sampleRate = 48000;
	settings.numOutputChannels = 2;
	settings.numInputChannels = 0;
	settings.bufferSize = 256;
	soundStream.setup(settings);

	char const* vlc_argv[] = { "" };
	int vlc_argc = sizeof(vlc_argv) / sizeof(*vlc_argv);
	player.load("https://acidpauli.pushtopull.org/files/FC-Shuttle/FC%20Shuttle%201303.MP3", vlc_argc, vlc_argv);
	player.setLoop(true);
	player.play();
}

//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer& buffer1) {
	if (player.isPlaying()) {
		player.ringBuffer.readIntoBuffer(buffer1);
	}
}

//--------------------------------------------------------------
void ofApp::update() {
	player.update();
	projectM.update();
	projectM.audio(player.audioData);
}

//--------------------------------------------------------------
void ofApp::draw() {
	player.draw(0, 0, 1280, 720);
	ofFill();
	cam.begin();
	projectM.bind();
	ofEnableDepthTest();
	box.draw();
	ofDisableDepthTest();
	projectM.unbind();
	cam.end();

	ofSetColor(225);
	ofDrawBitmapString(projectM.getPresetName(), 32, 700);
	ofDrawBitmapStringHighlight("FPS: " + ofToString(ofGetFrameRate()), 20, 20);
	ofDrawBitmapStringHighlight("Second: " + ofToString(player.getTime() / 1000), 20, 40);
	ofDrawBitmapStringHighlight("Press space for play, p for pause and m for switching the projectM preset!", 20, 60);
}

//--------------------------------------------------------------
void ofApp::exit() {
	soundStream.stop();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 32) {
		player.play();
	}
	else if (key == 112) {
		player.pause();
	}
	else if (key == 109) {
		projectM.randomPreset();
	}
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
void ofApp::windowResized(int w, int h) {
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
}

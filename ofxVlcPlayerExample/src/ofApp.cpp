#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofDisableArbTex();
    ofSetWindowTitle("ofxVlcPlayerExample");
    ofSetFrameRate(60);
    char const* vlc_argv[] = { "--input-repeat=100" };
    int vlc_argc = sizeof(vlc_argv) / sizeof(*vlc_argv);
    player.load("data/Big_Buck_Bunny_1080_10s_30MB.mp4", vlc_argc, vlc_argv);
    player.setLoop(true);
    player.play(); 
}

//--------------------------------------------------------------
void ofApp::update() {
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofSetColor(255);
    player.getTexture().draw(0, 0);
    ofSetColor(0, 255, 0);
    ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate()), 20, 20);
    ofDrawBitmapString("Second: " + ofToString(player.getTime() / 1000), 20, 40);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    player.pause();
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

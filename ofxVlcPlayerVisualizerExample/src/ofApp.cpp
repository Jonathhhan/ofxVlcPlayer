#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetWindowTitle("ofxVlcPlayerVisualizerExample");
    ofSetFrameRate(60);
    char const* vlc_argv[] = { "--vout=opengl", "--no-video", "--audio-visual=goom", "--goom-width=1280", "--goom-height=720" };
    int vlc_argc = sizeof(vlc_argv) / sizeof(*vlc_argv);
    player.load("https://acidpauli.pushtopull.org/files/2010/acid-pauli-vs-hometrainer-ritter-butzke-2010-05-23.mp3", vlc_argc, vlc_argv);
    player.setLoop(true);
    player.play();
}

//--------------------------------------------------------------
void ofApp::update() {
    player.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
    player.draw(0, 0, 1280, 720);
    ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate()), 20, 20);
    ofDrawBitmapString("Second: " + ofToString(player.getPosition() * player.getLength() / 1000), 20, 40);
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
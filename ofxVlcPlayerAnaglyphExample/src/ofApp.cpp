#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetWindowTitle("ofxVlcPlayerAnaglyphExample");
    ofSetFrameRate(60);
    char const* vlc_argv[] = { "--vout=opengl", "--start-paused", "--video-filter=anaglyph", "--adaptive-logic=highest" };
    int vlc_argc = sizeof(vlc_argv) / sizeof(*vlc_argv);
    player.load("https://rr7---sn-uxax4vopj5qx-cxge.googlevideo.com/videoplayback?expire=1718335936&ei=YGVrZtOUH5Gii9oPypGFwAU&ip=77.188.93.142&id=o-AOg9AJIMr0u1LGZMyPOcr99zCP5ZfSwoYZ4Abhv5rf1T&itag=22&source=youtube&requiressl=yes&xpc=EgVo2aDSNQ%3D%3D&mh=4W&mm=31%2C29&mn=sn-uxax4vopj5qx-cxge%2Csn-h0jelnez&ms=au%2Crdu&mv=m&mvi=7&pl=19&initcwndbps=1263750&bui=AbKP-1Owp9khMh3uh2ZxPLpCxRJtgMmKri3is2Cw_QERecT6mSAWwFIuxsKpjiwzI_5Eyfnzw4xg73RI&spc=UWF9f_X-1Zo81Z__U5-qr2men-htYZ7KjrymdUjLhhjzaPxNVx4opBKtivpn&vprv=1&svpuc=1&mime=video%2Fmp4&ns=g7JyijoANuS7PLGp6G6Tqx8Q&rqh=1&cnr=14&ratebypass=yes&dur=78.088&lmt=1711216767544109&mt=1718314154&fvip=2&c=WEB&sefc=1&txp=8218224&n=v_tbpcNw3XDKTzdN&sparams=expire%2Cei%2Cip%2Cid%2Citag%2Csource%2Crequiressl%2Cxpc%2Cbui%2Cspc%2Cvprv%2Csvpuc%2Cmime%2Cns%2Crqh%2Ccnr%2Cratebypass%2Cdur%2Clmt&sig=AJfQdSswRAIga7prtKqMuniSAIeqgYpABvTLVeaEAKvaV0Qhl5BXum8CIEJdxEJv97KWuW02hBNcJSVS-Bh-A6ciP0sv-e-N1Co2&lsparams=mh%2Cmm%2Cmn%2Cms%2Cmv%2Cmvi%2Cpl%2Cinitcwndbps&lsig=AHlkHjAwRQIgLcRDp1r54AlxWEneiGLMLl5FAvOqVssjUvK7xaj14VsCIQCERU7psPrEXRXAscmb1KfAUc-mrDRKXOlrXcJHwiJoGQ%3D%3D", vlc_argc, vlc_argv);
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

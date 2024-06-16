#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofDisableArbTex();
    ofSetWindowTitle("ofxVlcPlayer360Example");
    ofSetFrameRate(60);
    cam.setPosition(0,0,0);
    cam.setAutoDistance(false);
    char const* vlc_argv[] = { "--vout=opengl", "--start-paused", "--video-filter=transform", "--transform-type=hflip", "--adaptive-logic=highest" };
    int vlc_argc = sizeof(vlc_argv) / sizeof(*vlc_argv);
    player.load("https://rr6---sn-uxax4vopj5qx-cxge.googlevideo.com/videoplayback?expire=1718340235&ei=K3ZrZtalDrrOi9oPq5yAuAk&ip=77.188.93.142&id=o-AJHROOKw-Qk69115Gkl2uEZ5vZa4KCe7hXcfTVmp25Ms&itag=22&source=youtube&requiressl=yes&xpc=EgVo2aDSNQ%3D%3D&mh=T3&mm=31%2C29&mn=sn-uxax4vopj5qx-cxge%2Csn-h0jeener&ms=au%2Crdu&mv=m&mvi=6&pl=19&initcwndbps=1343750&bui=AbKP-1N1ZrFJbWALuyfcYrX0tpzKOzVEeqcTPxg_LgeaUGYINL1ixa72VWqomNch21ex0bDLayp9i-v_&spc=UWF9f8vYdUJumiNAY1F9PIznhVa7JI5Fb8f6L9EH5POJyeBZDtlZ1N9pGSHB&vprv=1&svpuc=1&mime=video%2Fmp4&ns=ZsfqSYanAakYWxjpaxSXeq0Q&rqh=1&cnr=14&ratebypass=yes&dur=214.134&lmt=1589300729212663&mt=1718317971&fvip=3&c=WEB&sefc=1&txp=5532232&n=-BuHL3rzjobLf1gV&sparams=expire%2Cei%2Cip%2Cid%2Citag%2Csource%2Crequiressl%2Cxpc%2Cbui%2Cspc%2Cvprv%2Csvpuc%2Cmime%2Cns%2Crqh%2Ccnr%2Cratebypass%2Cdur%2Clmt&sig=AJfQdSswRQIhALn8GX6HOQxsHWohBA7RFfneIO77H81uwk1m-jFWbOy6AiAQKUZk4hpRMwAVyKOd-051qdUNuC37CKSCAiTeyT-1Fg%3D%3D&lsparams=mh%2Cmm%2Cmn%2Cms%2Cmv%2Cmvi%2Cpl%2Cinitcwndbps&lsig=AHlkHjAwRAIgfJrkNOCg_ZXiw9v5m4rDfz27I7ijjtZqZKgvPTOx9kcCIGQ7NHIt_IyKrSgC4uySAIK_gARzMYRitZkS8khC2VL3", vlc_argc, vlc_argv);
    player.setLoop(true);
    player.play();
}

//--------------------------------------------------------------
void ofApp::update() {
    player.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
    cam.begin();
    player.getTexture().bind();
    sphere.draw();
    player.getTexture().unbind();
    cam.end();
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

#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main() {
	ofGLFWWindowSettings settings;
	settings.setSize(1280, 720);
	auto mainWindow = ofCreateWindow(settings);
	ofRunApp(mainWindow, make_shared<ofApp>());
	ofRunMainLoop();
}
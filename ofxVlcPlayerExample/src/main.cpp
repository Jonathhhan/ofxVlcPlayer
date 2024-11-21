#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main() {
	ofGLFWWindowSettings settings;
	settings.setSize(1280, 720);
	auto mainWindow = ofCreateWindow(settings);
	auto app = std::make_shared<ofApp>();
	ofRunApp(mainWindow, app);
	ofRunMainLoop();
}
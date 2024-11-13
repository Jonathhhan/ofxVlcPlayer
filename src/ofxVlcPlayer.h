#pragma once

#include "ofMain.h"
#include "vlc/vlc.h"

class ofxVlcPlayer {
    ofImage image;

    libvlc_instance_t* libvlc;
    libvlc_media_t* m;
    libvlc_media_player_t* mp;
    libvlc_event_manager_t* eventManager;

    int videoWidth, videoHeight;
    bool isLooping;

    // VLC Video callbaks
    static void* lockStatic(void* data, void** p_pixels);
    static void unlockStatic(void* data, void* id, void* const* p_pixels);
    static void displayStatic(void* data, void* id);

    void* lock(void** p_pixels);
    void unlock(void* id, void* const* p_pixels);
    void display(void* id);

    // VLC Event callbacks
    static void vlcEventStatic(const libvlc_event_t* event, void* data);
    void vlcEvent(const libvlc_event_t* event);

public:
    ofxVlcPlayer();
    virtual ~ofxVlcPlayer();
    void load(std::string name, int vlc_argc, char const* vlc_argv[]);
    void update();
    ofTexture& getTexture();
    void draw(float x, float y, float w, float h);
    void draw(float x, float y);
    void play();
    void pause();
    void stop();
    void setPosition(float pct);
    void setLoop(bool loop);
    bool getLoop() const;
    float getHeight() const;
    float getWidth() const;
    bool isPlaying();
    bool isSeekable();
    float getPosition();
    int getTime();
    void setTime(int ms);
    float getFps();
    float getLength();
    void setFrame(int frame);
    int getCurrentFrame();
    int getTotalNumFrames();
    void setVolume(int volume);
    void toggleMute();
};
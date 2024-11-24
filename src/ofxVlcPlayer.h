#pragma once

#include "ofMain.h"
#include "vlc/vlc.h"

class ofxVlcPlayer {
    libvlc_instance_t* libvlc;
    libvlc_media_t* media;
    libvlc_media_player_t* mediaPlayer;
    libvlc_event_manager_t* eventManager;

    ofTexture texture;
    shared_ptr<ofAppBaseWindow> vlcWindow;
    unsigned videoWidth;
    unsigned videoHeight;
    bool updated = false;
    bool isLooping = false;
    std::mutex texLock;
    GLuint tex[3];
    GLuint fbo[3];
    size_t idxRender = 0;
    size_t idxSwap = 1;
    size_t idxDisplay = 2;

    // VLC Video callbaks
    static bool setup(void** data, const libvlc_video_setup_device_cfg_t* cfg, libvlc_video_setup_device_info_t* out);
    static void cleanup(void* data);
    static bool resize(void* data, const libvlc_video_render_cfg_t* cfg, libvlc_video_output_cfg_t* render_cfg);
    static void swap(void* data);
    static bool make_current(void* data, bool current);
    static void* get_proc_address(void* data, const char* current);

    // VLC Event callbacks
    static void vlcEventStatic(const libvlc_event_t* event, void* data);
    void vlcEvent(const libvlc_event_t* event);

public:
    ofxVlcPlayer();
    virtual ~ofxVlcPlayer();
    void load(std::string name, int vlc_argc, char const* vlc_argv[]);
    void update();
    ofTexture& getTexture();
    void draw(float x, float y);
    void draw(float x, float y, float w, float h);
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
    float getLength();
    void setVolume(int volume);
    void toggleMute();
};

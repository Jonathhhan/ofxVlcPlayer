#include "ofxVlcPlayer.h"
 
ofxVlcPlayer::ofxVlcPlayer()
    : isLooping(true), libvlc(NULL), eventManager(NULL),
    m(NULL), mp(NULL), videoHeight(0), videoWidth(0) {}

ofxVlcPlayer::~ofxVlcPlayer() {}

void ofxVlcPlayer::load(std::string name, int vlc_argc, char const* vlc_argv[]) {

    libvlc = libvlc_new(vlc_argc, vlc_argv);
    if (!libvlc) {
        const char* error = libvlc_errmsg();
        cout << error << endl;
        return;
    }

    if (ofStringTimesInString(name, "://") == 1) {
        m = libvlc_media_new_location(name.c_str());
    }
    else {
        m = libvlc_media_new_path(name.c_str());
    }

    libvlc_media_parse_request(libvlc, m, libvlc_media_parse_local, 0);
    mp = libvlc_media_player_new_from_media(libvlc, m);
    unsigned int x, y;
    if (libvlc_video_get_size(mp, 0, &x, &y) != -1) {
        videoWidth = x;
        videoHeight = y;
    }
    else {
        videoWidth = 1280;
        videoHeight = 720;
    }
    std::cout << "Video size: " << videoWidth << " * " << videoHeight << std::endl;
    std::cout << "Video length: " << libvlc_media_get_duration(m) << " ms" << std::endl;

    libvlc_video_set_callbacks(mp, lockStatic, NULL, NULL, this);
    libvlc_video_set_format(mp, "RGBA", videoWidth, videoHeight, videoWidth * 4);
    // libvlc_video_set_format(mp, "RV32", videoWidth, videoHeight, videoWidth * 4); // for HAP transparency
    // libvlc_media_player_set_hwnd(mp, ofGetWin32Window());

    eventManager = libvlc_media_player_event_manager(mp);
    libvlc_event_attach(eventManager, libvlc_MediaPlayerStopping, vlcEventStatic, this);

    image.allocate(videoWidth, videoHeight, OF_IMAGE_COLOR_ALPHA);
}

void ofxVlcPlayer::update() {
    image.update();
}

ofTexture& ofxVlcPlayer::getTexture() {
    return image.getTexture();
}

void ofxVlcPlayer::draw(float x, float y, float w, float h) {
    image.draw(x, y, w, h);
}

void ofxVlcPlayer::draw(float x, float y) {
    getTexture().draw(x, y);
}

void ofxVlcPlayer::play() {
    libvlc_media_player_play(mp);
}

void ofxVlcPlayer::pause() {
    libvlc_media_player_pause(mp);
}

void ofxVlcPlayer::stop() {
    libvlc_media_player_stop_async(mp);
}

void ofxVlcPlayer::setPosition(float pct) {
    libvlc_media_player_set_position(mp, pct, true);
}

void ofxVlcPlayer::setLoop(bool loop) {
    isLooping = loop;
}

bool ofxVlcPlayer::getLoop() const {
    return isLooping;
}

float ofxVlcPlayer::getWidth() const {
    return videoWidth;
}

float ofxVlcPlayer::getHeight() const {
    return videoHeight;
}

bool ofxVlcPlayer::isPlaying() {
    return libvlc_media_player_is_playing(mp);
}

bool ofxVlcPlayer::isSeekable() {
    return libvlc_media_player_is_seekable(mp);
}

float ofxVlcPlayer::getPosition() {
    return libvlc_media_player_get_position(mp);
}

int ofxVlcPlayer::getTime() {
    return libvlc_media_player_get_time(mp);
}

void ofxVlcPlayer::setTime(int ms) {
    libvlc_media_player_set_time(mp, ms, true);
}

float ofxVlcPlayer::getLength() {
    return libvlc_media_player_get_length(mp);
}

void ofxVlcPlayer::setVolume(int volume) {
    libvlc_audio_set_volume(mp, volume);
}

void ofxVlcPlayer::toggleMute() {
    libvlc_audio_toggle_mute(mp);
}

void* ofxVlcPlayer::lockStatic(void* data, void** p_pixels) {
    return ((ofxVlcPlayer*)data)->lock(p_pixels);
}

void ofxVlcPlayer::vlcEventStatic(const libvlc_event_t* event, void* data) {
    ((ofxVlcPlayer*)data)->vlcEvent(event);
}

void ofxVlcPlayer::vlcEvent(const libvlc_event_t* event) {
    if (event->type == libvlc_MediaPlayerStopping) {
        if (isLooping) {
            mp = libvlc_media_player_new_from_media(libvlc, m);
            libvlc_video_set_callbacks(mp, lockStatic, NULL, NULL, this);
            libvlc_video_set_format(mp, "RGBA", videoWidth, videoHeight, videoWidth * 4);
            eventManager = libvlc_media_player_event_manager(mp);
            libvlc_event_attach(eventManager, libvlc_MediaPlayerStopping, vlcEventStatic, this);
            play();
        }
    }
}

void* ofxVlcPlayer::lock(void** p_pixels) {
    *p_pixels = image.getPixels().getData();
    return NULL;
}
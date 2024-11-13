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
        m = libvlc_media_new_location(libvlc, name.c_str());
    }
    else {
        m = libvlc_media_new_path(libvlc, name.c_str());
    }

    mp = libvlc_media_player_new_from_media(m);

    unsigned int x, y;
    if (libvlc_video_get_size(mp, 0, &x, &y) != -1) {
        videoWidth = x;
        videoHeight = y;
    }
    else {
        videoWidth = 1280;
        videoHeight = 720;
    }
    std::cout << "Video size: (" << videoWidth << ", " << videoHeight << ")" << std::endl;
    std::cout << "Video length: " << libvlc_media_get_duration(m) << "(ms)" << std::endl;

    libvlc_video_set_callbacks(mp, lockStatic, NULL, NULL, this);
    libvlc_video_set_format(mp, "RGBA", videoWidth, videoHeight, videoWidth * 4);
    // libvlc_video_set_format(mp, "RV32", videoWidth, videoHeight, videoWidth * 4); // for HAP transparency

    eventManager = libvlc_media_player_event_manager(mp);
    libvlc_event_attach(eventManager, libvlc_MediaPlayerEndReached, vlcEventStatic, this);

    image.allocate(videoWidth, videoHeight, OF_IMAGE_COLOR_ALPHA);

    libvlc_media_player_play(mp);
    libvlc_media_player_set_time(mp, 0);
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
    libvlc_media_player_stop(mp);
}

void ofxVlcPlayer::setPosition(float pct) {
    libvlc_media_player_set_position(mp, pct);
}

void ofxVlcPlayer::setLoop(bool loop) {
    isLooping = loop;
}

bool ofxVlcPlayer::getLoop() const {
    return isLooping;
}

float ofxVlcPlayer::getHeight() const {
    return videoHeight;
}

float ofxVlcPlayer::getWidth() const {
    return videoWidth;
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
    libvlc_media_player_set_time(mp, ms);
}

float ofxVlcPlayer::getFps() {
    return libvlc_media_player_get_fps(mp);
}

void ofxVlcPlayer::setFrame(int frame) {
    libvlc_media_player_set_time(mp, 1000 * frame / libvlc_media_player_get_fps(mp));
}

int ofxVlcPlayer::getCurrentFrame() {
    return libvlc_media_player_get_fps(mp) * libvlc_media_player_get_time(mp) / 1000;
}

int ofxVlcPlayer::getTotalNumFrames() {
    return libvlc_media_player_get_fps(mp) * libvlc_media_player_get_length(mp) / 1000;
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
    if (event->type == libvlc_MediaPlayerEndReached) {
        if (isLooping) {
            setTime(0);
            play();
        }
    }
}

void* ofxVlcPlayer::lock(void** p_pixels) {
    *p_pixels = image.getPixels().getData();
    return NULL;
}
#pragma once
#include "miniaudio.h"
#include <string>
#include <vector>

class AudioSystem {
public:
    bool init();
    void playSound(const std::string& filepath);
    void stopSound();
    void cleanUp();

private:
    ma_context context;

    ma_engine speakerEngine;
    ma_engine cableEngine;

    ma_device micRouterDevice;

    bool isContextInit = false;
    bool isSpeakerInit = false;
    bool isCableInit = false;
    bool isMicRouterInit = false;

    std::vector<ma_sound*> activeSpeakerSounds;
    std::vector<ma_sound*> activeCableSounds;

    static void duplexCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);
};
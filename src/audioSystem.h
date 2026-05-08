#pragma once
#include "miniaudio.h"
#include <string>

class AudioSystem {
public:
    bool init();
    void playSound(const std::string& filepath);
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

    static void duplexCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);
};
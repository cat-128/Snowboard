#include "stb_vorbis.c"

#undef L
#undef R
#undef C

#define MINIAUDIO_IMPLEMENTATION
#include "audioSystem.h"
#include <iostream>
#include <vector>

bool AudioSystem::init() {
    
    if (ma_context_init(NULL, 0, NULL, &context) != MA_SUCCESS) {
        std::cout << "Failed to initialize miniaudio\n";
        return false;
    }
    isContextInit = true;

    // Find the VB-Cable
    ma_device_info* pPlaybackInfos;
    ma_uint32 playbackCount;
    ma_context_get_devices(&context, &pPlaybackInfos, &playbackCount, NULL, NULL);

    ma_device_id vbCableID;
    bool foundCable = false;

    for (ma_uint32 i = 0; i < playbackCount; i++) {
        std::string deviceName = pPlaybackInfos[i].name;
        std::cout << "[" << i << "] " << deviceName << "\n";

        for (ma_uint32 i = 0; i < playbackCount; i++) {
            std::string deviceName = pPlaybackInfos[i].name;

            //
            if (!foundCable && (
                deviceName.find("CABLE Input") != std::string::npos ||
                deviceName.find("VB-Audio") != std::string::npos ||
                deviceName.find("Voicemeeter Input") != std::string::npos))
            {
                vbCableID = pPlaybackInfos[i].id;
                foundCable = true;
            }
        }
    }

    ma_engine_config speakerConfig = ma_engine_config_init();
    speakerConfig.pContext = &context;
    if (ma_engine_init(&speakerConfig, &speakerEngine) == MA_SUCCESS) {
        isSpeakerInit = true;
        std::cout << "Speaker engine started.\n";
    }

    if (foundCable) {
        ma_engine_config cableConfig = ma_engine_config_init();
        cableConfig.pContext = &context;
        cableConfig.pPlaybackDeviceID = &vbCableID;
        if (ma_engine_init(&cableConfig, &cableEngine) == MA_SUCCESS) {
            isCableInit = true;
            std::cout << "VB-Cable engine started.\n";
        }

        ma_device_config duplexConfig = ma_device_config_init(ma_device_type_duplex);
        duplexConfig.capture.pDeviceID = NULL;
        duplexConfig.playback.pDeviceID = &vbCableID;
        duplexConfig.capture.format = ma_format_f32;
        duplexConfig.playback.format = ma_format_f32;
        duplexConfig.capture.channels = 2;
        duplexConfig.playback.channels = 2;
        duplexConfig.sampleRate = 48000;
        duplexConfig.dataCallback = duplexCallback;

        if (ma_device_init(&context, &duplexConfig, &micRouterDevice) == MA_SUCCESS) {
            isMicRouterInit = true;
            ma_device_start(&micRouterDevice);
            std::cout << "Mic-to-Cable is working, big W's\n";
        }
        else {
            std::cout << "ERROR: Failed to start the goff\n";
        }
    }
    else {
        std::cout << "No Virtual Cable found.\n";
    }

    return true;
}

void AudioSystem::duplexCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount) {
    if (pOutput != nullptr && pInput != nullptr) {
        //copy mic input to vb-cable
        ma_uint32 bytesToCopy = frameCount * pDevice->playback.channels * ma_get_bytes_per_sample(pDevice->playback.format);
        memcpy(pOutput, pInput, bytesToCopy);
    }
}

void AudioSystem::playSound(const std::string& filepath) {
    std::cout << "Playing Sound: " << filepath << "\n";

    // Play to headphones
    if (isSpeakerInit) {
        ma_engine_play_sound(&speakerEngine, filepath.c_str(), NULL);
    }

    // Play to VB-cable
    if (isCableInit) {
        ma_engine_play_sound(&cableEngine, filepath.c_str(), NULL);
    }
}

void AudioSystem::cleanUp() {
    if (isMicRouterInit) {
        ma_device_uninit(&micRouterDevice);
    }
    if (isSpeakerInit) {
        ma_engine_uninit(&speakerEngine);
    }
    if (isCableInit) {
        ma_engine_uninit(&cableEngine);
    }
    if (isContextInit) {
        ma_context_uninit(&context);
    }
    std::cout << "AudioSystem cleaned up.\n";
}
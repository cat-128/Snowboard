#pragma once
#include <SDL3/SDL.h>
#include <string>
#include <vector>
#include <thread>
#include <atomic>

class AudioSystem {
public:
    bool init();
    void playSound();
    void cleanUp();

private:
    // Audio channels btw pretty cool
    SDL_AudioStream* sfxSpeakerStream = nullptr; // To headphones
    SDL_AudioStream* sfxCableStream = nullptr;   // to VB-Cable

    SDL_AudioStream* micCaptureStream = nullptr; // Microphone input
    SDL_AudioStream* micPlaybackStream = nullptr; // Mic -> VB-Cable

    // File data
    SDL_AudioSpec wavSpec;
    Uint8* wavBuffer = nullptr;
    Uint32 wavLength = 0;

    std::atomic<bool> threadRunning;
    std::thread audioThread;

    void microphoneLoop();
};
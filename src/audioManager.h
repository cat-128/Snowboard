#pragma once
#include <SDL3/SDL.h>
#include <iostream>
#include <unordered_map>
#include <string>

// this was like the file data in the audio system (cool)
struct sound {
    SDL_AudioSpec wavSpec;
    Uint8* wavBuffer = nullptr;
    Uint32 wavLength = 0;
    std::string name;
    SDL_Keycode keybind;
};

class AudioManager {
public:

    void loadAudio();

private:


};
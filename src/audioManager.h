#pragma once
#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include <string>

// this was like the file data in the audio system (cool)
struct sound {
    SDL_AudioSpec wavSpec;
    Uint8* wavBuffer = nullptr;
    Uint32 wavLength = 0;
    std::string name;
};

class AudioManager {
public:


private:


};
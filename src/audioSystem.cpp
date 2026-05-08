#include "audioSystem.h"
#include <iostream>

bool AudioSystem::init() {
    if (!SDL_Init(SDL_INIT_AUDIO)) {
        std::cout << "AudioSystem failed to initialize" << SDL_GetError() << "\n";
        return false;
    }

    if (!SDL_LoadWAV("resources/audio/bang.wav", &wavSpec, &wavBuffer, &wavLength)) {
        std::cout << "Couldn't load audio file: " << SDL_GetError() << "\n";
        return false;
    }

    // Find the VB-Cable Output
    int deviceCount = 0;
    SDL_AudioDeviceID* devices = SDL_GetAudioPlaybackDevices(&deviceCount);
    SDL_AudioDeviceID vbCableID = 0;

    for (int i = 0; i < deviceCount; i++) {
        std::string deviceName = SDL_GetAudioDeviceName(devices[i]);
        if (deviceName.find("CABLE Input") != std::string::npos) {
            vbCableID = devices[i];
            break;
        }
    }
    SDL_free(devices);

    // goofy ass channels
    sfxSpeakerStream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &wavSpec, nullptr, nullptr);

    // Mic input
    micCaptureStream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_RECORDING, &wavSpec, nullptr, nullptr);
    if (vbCableID != 0) {
        sfxCableStream = SDL_OpenAudioDeviceStream(vbCableID, &wavSpec, nullptr, nullptr);
        micPlaybackStream = SDL_OpenAudioDeviceStream(vbCableID, &wavSpec, nullptr, nullptr);
    }
    else {
        std::cout << "VB-Cable ID not found\n";
    }

    // Turn all the devices on
    if (sfxSpeakerStream) SDL_ResumeAudioDevice(SDL_GetAudioStreamDevice(sfxSpeakerStream));
    if (sfxCableStream) SDL_ResumeAudioDevice(SDL_GetAudioStreamDevice(sfxCableStream));
    if (micCaptureStream) SDL_ResumeAudioDevice(SDL_GetAudioStreamDevice(micCaptureStream));
    if (micPlaybackStream) SDL_ResumeAudioDevice(SDL_GetAudioStreamDevice(micPlaybackStream));

    // Start background thread
    if (micCaptureStream && micPlaybackStream) {
        threadRunning = true;
        audioThread = std::thread(&AudioSystem::microphoneLoop, this);
        std::cout << "Microphone background thread started!\n";
    }

    return true;
}

void AudioSystem::microphoneLoop() {
    while (threadRunning) {
        int availableBytes = SDL_GetAudioStreamAvailable(micCaptureStream);

        if (availableBytes > 0) {
            std::vector<Uint8> voiceBuffer(availableBytes);
            SDL_GetAudioStreamData(micCaptureStream, voiceBuffer.data(), availableBytes);
            SDL_PutAudioStreamData(micPlaybackStream, voiceBuffer.data(), availableBytes);
        }

        SDL_Delay(5);
    }
}

void AudioSystem::playSound() {
    std::cout << "Playing Bang!\n";

    // Push the sound to headphones
    if (sfxSpeakerStream) {
        SDL_PutAudioStreamData(sfxSpeakerStream, wavBuffer, wavLength);
    }

    // Push the sound to VB-Cable
    if (sfxCableStream) {
        SDL_PutAudioStreamData(sfxCableStream, wavBuffer, wavLength);
    }
}

void AudioSystem::cleanUp() {
    threadRunning = false;
    if (audioThread.joinable()) {
        audioThread.join();
    }

    // Destroy all 4 Channels (W)
    if (sfxSpeakerStream) SDL_DestroyAudioStream(sfxSpeakerStream);
    if (sfxCableStream) SDL_DestroyAudioStream(sfxCableStream);
    if (micCaptureStream) SDL_DestroyAudioStream(micCaptureStream);
    if (micPlaybackStream) SDL_DestroyAudioStream(micPlaybackStream);

    if (wavBuffer) SDL_free(wavBuffer);
    SDL_QuitSubSystem(SDL_INIT_AUDIO);

    std::cout << "AudioSystem cleaned up.\n";
}
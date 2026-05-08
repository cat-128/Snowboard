#include <iostream>
#include "renderer.h"
#include "audioSystem.h"

int main() {

	Renderer renderer;
	AudioSystem audio;

	renderer.init(400, 400, "snowboard");

	if (!audio.init()) {
		return -1;
	}

	bool isRunning = true;
	SDL_Event event;
	while (isRunning) {
			
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				isRunning = false;
			}

			if (event.type == SDL_EVENT_KEY_DOWN) {
				if (event.key.key == SDLK_SPACE) {
					audio.playSound("resources/audio/bang.wav");
				}

				if (event.key.key == SDLK_1) {
					audio.playSound("resources/audio/cave.wav");
				}
				if (event.key.key == SDLK_2) {
					audio.playSound("resources/audio/sounds/discord-notification.wav");
				}
				if (event.key.key == SDLK_3) {
					audio.playSound("resources/audio/sounds/drinkingNoise.wav");
				}
				if (event.key.key == SDLK_4) {
					audio.playSound("resources/audio/sounds/500.wav");
				}
				if (event.key.key == SDLK_5) {
					audio.playSound("resources/audio/sounds/w-speed.wav");
				}
				if (event.key.key == SDLK_6) {
					audio.playSound("resources/audio/sounds/ohMyGod.wav");
				}
				if (event.key.key == SDLK_7) {
					audio.playSound("resources/audio/sounds/fortnite.wav");
				}
			}
		}

		renderer.clear();
		renderer.present();
	}

	renderer.cleanUp();

	return 0;
}
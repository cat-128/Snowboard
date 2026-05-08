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
					audio.playSound();
				}
			}
		}

		renderer.clear();
		renderer.present();
	}

	renderer.cleanUp();

	return 0;
}
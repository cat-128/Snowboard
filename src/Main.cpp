#include <iostream>
#include "renderer.h"
#include "audioSystem.h"

int main() {

	Renderer renderer;

	renderer.init(400, 400, "snowboard");

	bool isRunning = true;
	SDL_Event event;
	while (isRunning) {
			
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				isRunning = false;
			}
		}

		renderer.clear();
		renderer.present();
	}

	renderer.cleanUp();

	return 0;
}
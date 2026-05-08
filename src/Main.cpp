#include <iostream>
#include "renderer.h"
#include "audioSystem.h"
#include "interface.h"

int main() {

	Renderer renderer;
	AudioSystem audio;
	Interface wholeUI;

	renderer.init(600, 370, "snowboard");

	SDL_Window* rawWindow = renderer.getWindow();
	SDL_Renderer* rawRenderer = renderer.getRenderer();

	if (!audio.init()) {
		return -1;
	}

	wholeUI.init(rawWindow, rawRenderer);

	bool isRunning = true;
	SDL_Event event;
	while (isRunning) {
			
		while (SDL_PollEvent(&event)) {

			wholeUI.processEvent(&event);

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

		wholeUI.StartFrame();
		wholeUI.drawFrame("Snowboard");

		renderer.clear();
		wholeUI.ImGuiRender(rawRenderer);
		renderer.present();
	}

	wholeUI.cleanUp();
	renderer.cleanUp();

	return 0;
}
#include <SDL3/SDL.h>
#include <iostream>

class Renderer {
public:

	void init(int width, int height, const char* title);
	void clear();
	void present();
	void cleanUp();

	SDL_Renderer* getRenderer();
	SDL_Window* getWindow();

private:

	SDL_Window* window = nullptr;
	SDL_Renderer* SDL_Renderer = nullptr;
};
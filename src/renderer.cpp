#include "renderer.h"

void Renderer::init(int width, int height, const char* title) {

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << "SDL Video failed to init! Error: " << SDL_GetError() << "\n";
    }

    if (!SDL_CreateWindowAndRenderer(title, width, height, 0, &window, &SDL_Renderer)) {
        std::cout << "SDL window and renderer could not be created" << std::endl;
    }
}

void Renderer::present() {
    SDL_RenderPresent(SDL_Renderer);
}

void Renderer::clear() {
    SDL_SetRenderDrawColor(SDL_Renderer, 35, 67, 92, 255);
    SDL_RenderClear(SDL_Renderer);
}

SDL_Renderer* Renderer::getRenderer() {
    return SDL_Renderer;
}

SDL_Window* Renderer::getWindow() {
    return window;
}

void Renderer::cleanUp() {
    if (SDL_Renderer) SDL_DestroyRenderer(SDL_Renderer);
    if (window) SDL_DestroyWindow(window);

    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}
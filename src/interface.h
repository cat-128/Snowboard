#pragma once

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
#include "audioSystem.h"
#include <iostream>

class Interface {
public:

	void init(SDL_Window* window, SDL_Renderer* renderer);
	void processEvent(SDL_Event* event);
	void StartFrame();
	void EndFrame();
	void Layout(AudioSystem& audio);
	void SetStyles();

	void drawFrame(const char* title);
	void ImGuiRender(SDL_Renderer* renderer);
	void cleanUp();

private:


};
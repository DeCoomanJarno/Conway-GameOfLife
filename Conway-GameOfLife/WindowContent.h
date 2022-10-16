#pragma once
#include <SDL_render.h>
#include <SDL_video.h>

#include "Singleton.h"

struct WindowContent : public Singleton<WindowContent>
{
	SDL_Window* m_pWindow = nullptr;
	SDL_Renderer* m_pRenderer = nullptr;
};
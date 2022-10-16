
#include "GameManager.h"
#include "GameOfLife.h"
#include "SDL.h"
#include "WindowContent.h"
#undef main

void InitGames();
void HandleInput();

int main() 
{
	// -- Create Window --
	auto& windowContent = WindowContent::GetInstance();
	const SDL_Rect windowDimensions{ SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,480,480 };

	windowContent.m_pWindow = SDL_CreateWindow(
		"Conway, Game Of Life - De Cooman Jarno", 
		windowDimensions.x, 
		windowDimensions.y,
		windowDimensions.w, 
		windowDimensions.h,
		SDL_WINDOW_RESIZABLE);
	SDL_assert(windowContent.m_pWindow);


	// -- Create Renderer --
	windowContent.m_pRenderer = SDL_CreateRenderer(windowContent.m_pWindow, -1, NULL);
	SDL_assert(windowContent.m_pRenderer);

	SDL_SetRenderDrawBlendMode(windowContent.m_pRenderer, SDL_BLENDMODE_BLEND);

	// -- GameLoop --
	InitGames();
	bool isRunning = true;
	while (isRunning)
	{
		HandleInput();
		GameManager::GetInstance().HandleEvents(isRunning);
		GameManager::GetInstance().Update();
		GameManager::GetInstance().Render();
	}

	// -- Free Memory --
	GameManager::GetInstance().CleanUp();

	SDL_Quit();

	return 0;
}

//simple render function
void InitGames()
{
	auto& gameManager = GameManager::GetInstance();
	gameManager.AddGame(new GameOfLife());
}

void HandleInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		const auto scancode = event.key.keysym.scancode;
		if(event.type == SDL_KEYDOWN)
		{
			if(scancode >= SDL_SCANCODE_1 && scancode <= SDL_SCANCODE_0)
			{
				auto& gameManager = GameManager::GetInstance();
				gameManager.CleanUp();
				gameManager.AddGame(new GameOfLife(scancode - SDL_SCANCODE_1 + 1));
			}
		}
	}
}

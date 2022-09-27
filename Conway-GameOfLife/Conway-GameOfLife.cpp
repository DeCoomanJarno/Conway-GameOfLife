
#include "GameManager.h"
#include "GameOfLife.h"
#include "SDL.h"
#undef main

void InitGames();

int main() 
{
	// -- Create Window --
	SDL_Window* pWindow = nullptr;
	const SDL_Rect windowDimensions{ SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,480,640 };

	pWindow = SDL_CreateWindow(
		"Conway, Game Of Life - De Cooman Jarno", 
		windowDimensions.x, 
		windowDimensions.y,
		windowDimensions.w, 
		windowDimensions.h,
		SDL_WINDOW_RESIZABLE);
	SDL_assert(pWindow);


	// -- Create Renderer --
	SDL_Renderer* pRenderer = nullptr;

	pRenderer = SDL_CreateRenderer(pWindow, -1, NULL);
	SDL_assert(pRenderer);

	SDL_SetRenderDrawBlendMode(pRenderer, SDL_BLENDMODE_BLEND);

	// -- GameLoop --
	InitGames();
	bool isRunning = true;
	while (isRunning)
	{
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


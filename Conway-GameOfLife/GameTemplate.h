#pragma once
#include <SDL.h>
class GameTemplate
{
public:
	GameTemplate() = default;
	virtual ~GameTemplate() = default;

	GameTemplate(const GameTemplate& other) = delete;
	GameTemplate(GameTemplate&& other) noexcept = delete;
	GameTemplate& operator=(const GameTemplate& other) = delete;
	GameTemplate& operator=(GameTemplate&& other) noexcept = delete;

	virtual void Update(){}
	virtual void Render(){}
	virtual void HandleEvents(const SDL_Event&){}

private:
};


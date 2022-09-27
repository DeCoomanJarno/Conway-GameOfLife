#pragma once
#include "GameTemplate.h"
class GameOfLife final: public GameTemplate
{
public:
	GameOfLife() = default;
	~GameOfLife() override = default;

	GameOfLife(const GameOfLife& other) = delete;
	GameOfLife(GameOfLife&& other) noexcept = delete;
	GameOfLife& operator=(const GameOfLife& other) = delete;
	GameOfLife& operator=(GameOfLife&& other) noexcept = delete;

	void HandleEvents(const SDL_Event& event) override{}
	void Update() override{}
	void Render() override{}
};


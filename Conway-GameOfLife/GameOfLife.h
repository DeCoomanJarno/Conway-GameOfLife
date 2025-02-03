#pragma once
#include "GameTemplate.h"
#include "TMatrix.h"

class GameOfLife final: public GameTemplate
{
public:
	GameOfLife(const int scale = 1);
	~GameOfLife() override;

	GameOfLife(const GameOfLife& other) = delete;
	GameOfLife(GameOfLife&& other) noexcept = delete;
	GameOfLife& operator=(const GameOfLife& other) = delete;
	GameOfLife& operator=(GameOfLife&& other) noexcept = delete;

	void HandleEvents(const SDL_Event& event) override;
	void Update() override;
	void Resize(int new_width, int new_height);
	void Render() override;
private:
	static void RenderPixel(int x, int y);
	bool IsAlive(int x, int y) const;
	TMatrix<bool>* m_pGrid;
	TMatrix<bool>* m_pBuffer;
	const int m_Scale = 1;
};


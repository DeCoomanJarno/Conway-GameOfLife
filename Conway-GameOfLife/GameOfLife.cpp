#include "GameOfLife.h"

#include <algorithm>

#include "WindowContent.h"

GameOfLife::GameOfLife(const int scale)
	:m_Scale(scale)
{
	const auto pWindow = WindowContent::GetInstance().m_pWindow;
	int width, height;
	SDL_GetWindowSize(pWindow, &width, &height);
	m_pGrid = new TMatrix<bool>(width / m_Scale, height / m_Scale);
	m_pBuffer = new TMatrix<bool>(width / m_Scale, height / m_Scale);
	for (int x = 0; x < width / m_Scale; x++)
	{
		for (int y = 0; y < height / m_Scale; y++)
		{
			m_pGrid->Get(x,y) = false;
		}
	}
	for (int x = 0; x < width / m_Scale; x++)
	{
		for (int y = 0; y < height / m_Scale; y++)
		{
			m_pGrid->Get(x,y) = (rand() % 100) < 30;
		}
	}
}

void GameOfLife::HandleEvents(const SDL_Event& )
{
}

void GameOfLife::Update()
{
	const int width{ m_pGrid->Rows() }, height{ m_pGrid->Cols() };
	
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height;y++)
		{
			if(x == 26 && y == 16)
				continue;
			m_pBuffer->Get(x, y) = IsAlive(x, y);
		}
	}
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			m_pGrid->Get(x, y) = m_pBuffer->Get(x, y);
		}
	}
}

void GameOfLife::Render()
{
	const auto pRenderer = WindowContent::GetInstance().m_pRenderer;
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(pRenderer);
	SDL_RenderSetScale(pRenderer, static_cast<float>(m_Scale), static_cast<float>(m_Scale));
	const int width{ m_pGrid->Rows() }, height{ m_pGrid->Cols() };
	for (int x = 0; x < width;x++)
	{
		for (int y = 0; y < height; y++)
		{
			if(m_pGrid->Get(x,y))
			{
				RenderPixel(x, y);
			}
		}
	}
	SDL_Delay(20);
	SDL_RenderPresent(pRenderer);
}

void GameOfLife::RenderPixel(int x, int y)
{
	const auto pRenderer = WindowContent::GetInstance().m_pRenderer;
	SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawPoint(pRenderer, x, y);
}

bool GameOfLife::IsAlive(int x, int y) const
{
	const int width{ m_pGrid->Rows() - 1 }, height{ m_pGrid->Cols() - 1 };
	int alive = 0;
	if (x > 0 && m_pGrid->Get(x - 1, y) == true) // Left 4
		++alive;

	if (x < width && m_pGrid->Get(x + 1, y) == true) // Right 6
		++alive;

	if (y > 0 && m_pGrid->Get(x, y - 1) == true) // Top 2
		++alive;

	if (y < height && m_pGrid->Get(x, y + 1) == true) // Bottom 8
		++alive;

	if (x > 0 && y > 0 && m_pGrid->Get(x - 1, y - 1) == true) // Top Left 1
		++alive;

	if (x < width && y > 0 && m_pGrid->Get(x + 1, y - 1) == true) // Top Right 3
		++alive;

	if (y < height && x > 0 && m_pGrid->Get(x - 1, y + 1) == true) // Bottom Left 7
		++alive;

	if (y < height && x < width && m_pGrid->Get(x + 1, y + 1) == true) // Bottom Right 9
		++alive;

	if (m_pGrid->Get(x, y) == true && (alive == 2 || alive == 3))
	{
		return true;
	}

	if (m_pGrid->Get(x,y) == false && alive == 3)
	{
		return true;
	}

	return false;
}

#include "GameManager.h"
#include <algorithm>
#include <iostream>

void GameManager::HandleEvents(SDL_Event event) const
{
	m_pCurGame->HandleEvents(event);  // Handle events specific to your game
}


void GameManager::Update() const
{
	m_pCurGame->Update();
}

void GameManager::Render() const
{
	m_pCurGame->Render();
}

void GameManager::AddGame(GameTemplate* pGame)
{
	if (m_pCurGame == nullptr)
		m_pCurGame = pGame;

	m_pGames.emplace_back(pGame);
}

void GameManager::RemoveGame(GameTemplate* pGame)
{
	m_pGames.erase(std::ranges::remove(m_pGames, pGame).begin());
}

void GameManager::SetActiveGame(GameTemplate* pGame)
{
	m_pCurGame = pGame;
}

void GameManager::CleanUp()
{
	m_pCurGame = nullptr;
	for (size_t i = 0; i < m_pGames.size(); ++i)
	{
		delete m_pGames[i];
		m_pGames[i] = nullptr;
	}
}
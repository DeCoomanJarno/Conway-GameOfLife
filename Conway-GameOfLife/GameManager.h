#pragma once
#include "GameTemplate.h"
#include <vector>

#include "Singleton.h"


class GameManager final : public Singleton<GameManager>
{
public:
	GameManager() = default;
	~GameManager() = default;

	GameManager(const GameManager& other) = delete;
	GameManager(GameManager&& other) noexcept = delete;
	GameManager& operator=(const GameManager& other) = delete;
	GameManager& operator=(GameManager&& other) noexcept = delete;

	void Update() const;
	void Render() const;
	void HandleEvents(SDL_Event event) const;

	void CleanUp();

	void AddGame(GameTemplate* pGame);
	void RemoveGame(GameTemplate* pGame);

	void SetActiveGame(GameTemplate* pGame);

private:
	GameTemplate* m_pCurGame = nullptr;
	std::vector<GameTemplate*> m_pGames{};
};


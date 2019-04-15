#include "..\stdafx.h"
#include "GameManager.h"

void GameManager::IncreaseCoin(int amount)
{
	GameManager::CoinsCollected += amount;
}

void GameManager::DecreaseCoin(int amount)
{
	GameManager::CoinsCollected -= (amount == -1) ? GameManager::CoinLoseAmount : amount;
	if (GameManager::CoinsCollected < 0)
		GameManager::CoinsCollected = 0;
}

void GameManager::ResetGameTime(float time)
{
	GameTimeRemaining = time;
}

void GameManager::ResetGameStat()
{
	GameManager::RemainingCoins = 0;
	GameManager::CoinsCollected = 0;
	GameManager::PacmanFlagScore = 0.0f;
	GameManager::GhostFlagScore = 0.0f;
}

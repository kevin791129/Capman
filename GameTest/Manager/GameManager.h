#pragma once
#include "..\Object\ActorObject.h"
#include "..\TileMap.h"

class GameManager
{
public:
	static ActorList* ActorList;
	static TileMap* Map;
	static int RemainingCoins;
	static int CoinsCollected;
	static int CoinLoseAmount;
	static float PacmanFlagScore;
	static float GhostFlagScore;
	static float GameTimeRemaining;
	static bool ChangeScene;
	static int SceneNum;
	static int ControlActor;
public:
	static void IncreaseCoin(int amount = 1);
	static void DecreaseCoin(int amount = -1);
	static void ResetGameTime(float time = 60.0f);
	static void ResetGameStat();
};
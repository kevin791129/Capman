//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
#include "app\app.h"
#include "Scene\Scene.h"
#include "Scene\MenuScene.h"
#include "Scene\GameScene.h"

ActorList* GameManager::ActorList = nullptr;
TileMap* GameManager::Map = nullptr;
int GameManager::RemainingCoins = 0;
int GameManager::CoinsCollected = 0;
int GameManager::CoinLoseAmount = 10;
float GameManager::PacmanFlagScore = 0.0f;
float GameManager::GhostFlagScore = 0.0f;
float GameManager::GameTimeRemaining = 0.0f;
bool GameManager::ChangeScene = false;
int GameManager::SceneNum = 0;
int GameManager::ControlActor = 0;

Scene* currentScene;

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	currentScene = new MenuScene();
	currentScene->InitScene();
	GameManager::ChangeScene = false;
	GameManager::SceneNum = 0;
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	srand(time(0));

    static const float MIN_FRAMERATE = (1000 / 20);
    if (deltaTime > MIN_FRAMERATE)
        deltaTime = MIN_FRAMERATE;
	
	currentScene->UpdateScene(deltaTime);

	if (GameManager::ChangeScene)
	{
		delete currentScene;
		if (GameManager::SceneNum == 0)
		{
			currentScene = new GameScene();
			currentScene->InitScene();
			GameManager::SceneNum = 1;
		}
		else
		{
			currentScene = new MenuScene();
			currentScene->InitScene();
			GameManager::SceneNum = 0;
		}
		GameManager::ChangeScene = false;
	}
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine or Print) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{
	currentScene->RenderScene();
}

//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{
	delete currentScene;
}
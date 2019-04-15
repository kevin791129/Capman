#pragma once
#include "Scene.h"
#include "..\TileMap.h"
#include "..\Object\TextObject.h"
#include "..\Object\Pacman.h"
#include "..\Object\Coin.h"
#include "..\Object\Ghost.h"
#include "..\Object\Flag.h"
#include "..\Manager\ActorManager.h"
#include "..\Manager\AIManager.h"
#include "..\Manager\GameManager.h"

class GameScene : public Scene
{
private:
	bool _gameOverDoOnce;
public:
	ActorManager m_ActorManager;
	AIManager m_AImanager;
	Pacman* pacman;
	Ghost* ghost;
	Ghost* ghost2;
	Ghost* ghost3;
	Flag* flag;
	TextObject* debug;
public:
	GameScene() : _gameOverDoOnce(true) { }
	~GameScene();
	void GameScene::InitScene() override;
	void GameScene::UpdateScene(float deltaTime) override;
	void GameScene::RenderScene() override;
};
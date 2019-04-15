#include "..\stdafx.h"
#include "GameScene.h"

GameScene::~GameScene()
{
	delete GameManager::Map;
}

void GameScene::InitScene()
{
	GameManager::ResetGameTime(60.0f);
	GameManager::Map = new TileMap();
	SceneActorList = GameManager::Map->ResetMap();
	pacman = new Pacman(GameManager::Map->GetTile(1, 1));
	ghost = new Ghost(GameManager::Map->GetTile(18, 1), 1.0f, 0.0f, 0.0f);
	if (GameManager::ControlActor == 0)
	{
		pacman->SetControl(true);
		ghost->SetControl(false);
	}
	else if (GameManager::ControlActor == 1)
	{
		pacman->SetControl(false);
		ghost->SetControl(true);
	}
	else
	{
		pacman->SetControl(false);
		ghost->SetControl(false);
	}
	ghost2 = new Ghost(GameManager::Map->GetTile(9, 21), 0.0f, 1.0f, 0.0f);
	ghost2->SetControl(false);
	ghost3 = new Ghost(GameManager::Map->GetTile(11, 21), 0.7f, 0.2f, 0.6f);
	ghost3->SetControl(false);
	flag = new Flag(GameManager::Map->GetTile(13, 6));
	SceneActorList.push_back(pacman);
	SceneActorList.push_back(ghost);
	SceneActorList.push_back(ghost2);
	SceneActorList.push_back(ghost3);
	SceneActorList.push_back(flag);
	GameManager::ActorList = &SceneActorList;
	m_AImanager.InitAI();

	TextObject* coinCount = new TextObject();
	coinCount->SetPosition(250, 740);
	SceneTextList.push_back(coinCount);
	TextObject* pacmanScore = new TextObject();
	pacmanScore->SetPosition(50, 740);
	SceneTextList.push_back(pacmanScore);
	TextObject* ghostScore = new TextObject();
	ghostScore->SetPosition(630, 740);
	SceneTextList.push_back(ghostScore);
	TextObject* endResult = new TextObject();
	endResult->SetPosition(400, 430);
	SceneTextList.push_back(endResult);
	TextObject* pacmanState = new TextObject();
	pacmanState->SetPosition(100, 4);
	TextObject* ghost1State = new TextObject();
	ghost1State->SetPosition(200, 4);
	TextObject* ghost2State = new TextObject();
	ghost2State->SetPosition(300, 4);
	TextObject* ghost3State = new TextObject();
	ghost3State->SetPosition(400, 4);
	SceneTextList.push_back(pacmanState);
	SceneTextList.push_back(ghost1State);
	SceneTextList.push_back(ghost2State);
	SceneTextList.push_back(ghost3State);
}

void GameScene::UpdateScene(float deltaTime)
{
	GameManager::GameTimeRemaining -= deltaTime / 1000.0f;
	if (GameManager::GameTimeRemaining < 0)
	{
		if (GameManager::GameTimeRemaining < -3)
		{
			GameManager::ChangeScene = true;
		}
		return;
	}
		

	pacman->UpdateObject(deltaTime);
	ghost->UpdateObject(deltaTime);
	ghost2->UpdateObject(deltaTime);
	ghost3->UpdateObject(deltaTime);
	flag->UpdateObject(deltaTime);
	m_ActorManager.CheckForCollisions();

	
	for (int i = 0; i < 4; i++)
	{
		int state = m_AImanager.StateMachines[i]->_currentState;
		switch (state)
		{
		case 0:
			SceneTextList[i + 4]->SetString("Attack");
			break;
		case 1:
			SceneTextList[i + 4]->SetString("Grap");
			break;
		case 2:
			SceneTextList[i + 4]->SetString("Defend");
			break;
		default:
			SceneTextList[i + 4]->SetString("Human");
		}
	}
	
	if (!pacman->_AIControl)
	{
		SceneTextList[4]->SetString("Human");
	}
	else if (!ghost->_AIControl)
	{
		SceneTextList[5]->SetString("Human");
	}

	m_AImanager.ControlAIActors();


	float xAxis = App::GetController().GetLeftThumbStickX();
	float yAxis = App::GetController().GetLeftThumbStickY();

	if (!pacman->_AIControl || !ghost->_AIControl)
	{
		int move = -1;
		if (yAxis > 0.0f)
		{
			move = 0;
		}
		else if (yAxis < 0.0f)
		{
			move = 2;
		}
		else if (xAxis > 0.0f)
		{
			move = 1;
		}
		else if (xAxis < 0.0f)
		{
			move = 3;
		}
		if (move > -1)
		{
			if (!pacman->_AIControl)
			{
				int pacmanMapX = pacman->_currentTile->_mapRow + directions[move][0];
				int pacmanMapY = pacman->_currentTile->_mapCol + directions[move][1];
				pacman->StartMove(move);
			}
			else if (!ghost->_AIControl)
			{
				int ghostMapX = ghost->_currentTile->_mapRow + directions[move][0];
				int ghostMapY = ghost->_currentTile->_mapCol + directions[move][1];
				ghost->StartMove(move);
			}
		}
	}

	m_ActorManager.DestoryActors();

	std::string pac = "Cap-man: ";
	std::string ghost = "Ghost: ";
	SceneTextList[0]->SetString(std::to_string(GameManager::CoinsCollected));
	SceneTextList[1]->SetString(pac.append(std::to_string((int)GameManager::PacmanFlagScore)));
	SceneTextList[2]->SetString(ghost.append(std::to_string((int)GameManager::GhostFlagScore)));
}

void GameScene::RenderScene()
{
	GameManager::Map->Render();
	for (ActorObject* actor : SceneActorList)
	{
		actor->DrawObject();
	}
	if (GameManager::GameTimeRemaining < 0.0f)
	{
		App::DrawQuad(312, 339, 712, 509, 1, 0.5, 0.2);
		if ((int)GameManager::PacmanFlagScore + GameManager::CoinsCollected > (int)GameManager::GhostFlagScore)
		{
			SceneTextList[3]->SetString("Cap-man Wins");
		}
		else if ((int)GameManager::PacmanFlagScore + GameManager::CoinsCollected < (int)GameManager::GhostFlagScore)
		{
			SceneTextList[3]->SetString("Ghost Wins");
		}
		else
		{
			SceneTextList[3]->SetString("Tie");
		}
	}
	for (TextObject* text : SceneTextList)
	{
		text->DrawObject();
	}
}

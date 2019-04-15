#include "..\stdafx.h"
#include "MenuScene.h"
#include "..\Manager\GameManager.h"

void MenuScene::InitScene()
{
	GameManager::ResetGameTime();
	GameManager::ResetGameStat();

	TextObject* title = new TextObject();
	title->SetPosition(410, 550);
	title->SetString("Cap-man the Flag");
	TextObject* howToPlay = new TextObject();
	howToPlay->SetPosition(150, 400);
	howToPlay->SetString("How To Play:");
	TextObject* howToPlay2 = new TextObject();
	howToPlay2->SetPosition(170, 370);
	howToPlay2->SetString("Cap-man and ghosts fight for the flag. Coin Cap-man collects ");
	TextObject* howToPlay3 = new TextObject();
	howToPlay3->SetPosition(170, 340);
	howToPlay3->SetString("will be a bonus at the end of the game, and it losses 5 coins ");
	TextObject* howToPlay4 = new TextObject();
	howToPlay4->SetPosition(170, 310);
	howToPlay4->SetString("everytime it touches a ghost.");

	_pBtn = new TextObject();
	_pBtn->SetPosition(200, 200);
	_pBtn->SetString("Cap-man");

	_gBtn = new TextObject();
	_gBtn->SetPosition(460, 200);
	_gBtn->SetString("Ghost");

	_sBtn = new TextObject();
	_sBtn->SetPosition(650, 200);
	_sBtn->SetString("Spectator");

	SceneTextList.push_back(title);
	SceneTextList.push_back(howToPlay);
	SceneTextList.push_back(howToPlay2);
	SceneTextList.push_back(howToPlay3);
	SceneTextList.push_back(howToPlay4);
	SceneTextList.push_back(_pBtn);
	SceneTextList.push_back(_gBtn);
	SceneTextList.push_back(_sBtn);
}

void MenuScene::UpdateScene(float deltaTime)
{
	if (_currentSelect == 0)
		_pBtn->SetColor(1, 1, 0);
	else
		_pBtn->SetColor(1, 1, 1);

	if (_currentSelect == 1)
		_gBtn->SetColor(1, 1, 0);
	else
		_gBtn->SetColor(1, 1, 1);

	if (_currentSelect == 2)
		_sBtn->SetColor(1, 1, 0);
	else
		_sBtn->SetColor(1, 1, 1);

	float xAxis = App::GetController().GetLeftThumbStickX();
	float yAxis = App::GetController().GetLeftThumbStickY();
	if (yAxis > 0.0f)
	{
		GameManager::ControlActor = _currentSelect;
		GameManager::ChangeScene = true;
	}
	else if (yAxis < 0.0f)
	{
		GameManager::ControlActor = _currentSelect;
		GameManager::ChangeScene = true;
	}
	else if (xAxis > 0.0f)
	{
		_currentSelect++;
		if (_currentSelect > 2)
			_currentSelect = 0;
	}
	else if (xAxis < 0.0f)
	{
		_currentSelect--;
		if (_currentSelect < 0)
			_currentSelect = 2;
	}
}

#pragma once
#include "Scene.h"

class MenuScene : public Scene
{
public:
	TextObject* _pBtn;
	TextObject* _gBtn;
	TextObject* _sBtn;
	int _currentSelect = 0;
public:
	MenuScene() { }
	~MenuScene() { }
	void MenuScene::InitScene() override;
	void MenuScene::UpdateScene(float deltaTime) override;
};
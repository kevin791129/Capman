#pragma once
#include "..\Object\TextObject.h"
#include "..\Object\ActorObject.h"

class Scene
{
public:
	std::vector<TextObject*> SceneTextList;
	ActorList SceneActorList;
public:
	Scene() { }
	~Scene();
	virtual void InitScene() = 0;
	virtual void UpdateScene(float deltaTime);
	virtual void RenderScene();
};
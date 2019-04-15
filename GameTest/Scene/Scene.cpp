#include "..\stdafx.h"
#include "Scene.h"

Scene::~Scene()
{
	for (TextObject* text : SceneTextList)
	{
		delete text;
	}
	for (ActorObject* actor : SceneActorList)
	{
		delete actor;
	}
	SceneTextList.clear();
	SceneActorList.clear();
}

void Scene::UpdateScene(float deltaTime)
{
	for (ActorObject* actor : SceneActorList)
	{
		actor->UpdateObject(deltaTime);
	}
}

void Scene::RenderScene()
{
	for (ActorObject* actor : SceneActorList)
	{
		actor->DrawObject();
	}
	for (TextObject* text : SceneTextList)
	{
		text->DrawObject();
	}
}


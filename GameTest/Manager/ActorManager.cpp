#include "..\stdafx.h"
#include "ActorManager.h"
#include "GameManager.h"

void ActorManager::CheckForCollisions()
{
	//Nested check bad performance
	for (int i = 0; i < GameManager::ActorList->size(); i++)
	{
		for (int j = i + 1; j < GameManager::ActorList->size(); j++)
		{
			bool collide = ActorObject::HasCollision(GameManager::ActorList->at(i), GameManager::ActorList->at(j));
			if (collide)
			{
				GameManager::ActorList->at(i)->ResolveCollision(GameManager::ActorList->at(j)->_type, GameManager::ActorList->at(j));
				GameManager::ActorList->at(j)->ResolveCollision(GameManager::ActorList->at(i)->_type, GameManager::ActorList->at(i));
			}
		}
	}
}

void ActorManager::DestoryActors()
{
	std::vector<int> destoryIndex;
	for (int index = 0; index < GameManager::ActorList->size(); index++)
	{
		if (GameManager::ActorList->at(index)->_toBeDestory)
		{
			destoryIndex.push_back(index);
		}
	}
	for (int index = destoryIndex.size() - 1; index >= 0; index--)
	{
		delete GameManager::ActorList->at(destoryIndex[index]);
		GameManager::ActorList->erase(GameManager::ActorList->begin() + destoryIndex[index]);
	}
}

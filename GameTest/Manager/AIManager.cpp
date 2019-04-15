#include "..\stdafx.h"
#include "AIManager.h"
#include "GameManager.h"

AIManager::~AIManager()
{
	for (StateMachine* sm : StateMachines)
	{
		delete sm;
	}
}

void AIManager::InitAI()
{
	int listSize = GameManager::ActorList->size();
	pacman = dynamic_cast<Pacman*>(GameManager::ActorList->at(listSize - 5));
	ghost[0] = dynamic_cast<Ghost*>(GameManager::ActorList->at(listSize - 4));
	ghost[1] = dynamic_cast<Ghost*>(GameManager::ActorList->at(listSize - 3));
	ghost[2] = dynamic_cast<Ghost*>(GameManager::ActorList->at(listSize - 2));
	flag = dynamic_cast<Flag*>(GameManager::ActorList->at(listSize - 1));

	for (int i = 0; i < 4; i++)
	{
		StateMachine* sm = new StateMachine(EStates::Grab);
		sm->InitStateMachine(i, pacman, ghost[0], ghost[1], ghost[2], flag, new AttackState(sm), new GrabState(sm), new DefendState(sm));
		StateMachines[i] = sm;
	}
	
}

void AIManager::ControlAIActors()
{
	for (StateMachine* sm : StateMachines)
	{
		if (sm->_self == 0)
		{
			if (!sm->_pacman->_AIControl || sm->_pacman->_freezeTime > 0.0f)
				continue;
		}
		else
		{
			if (!sm->_ghosts[sm->_self - 1]->_AIControl || sm->_ghosts[sm->_self - 1]->_freezeTime > 0.0f)
				continue;
		}
		sm->SetState(sm->CheckIfChangeState());
		sm->DoStateAction();
	}
}

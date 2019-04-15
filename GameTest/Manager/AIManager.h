#pragma once
#include "..\Object\ActorObject.h"
#include "..\TileMap.h"
#include "..\Object\Pacman.h"
#include "..\Object\Ghost.h"
#include "..\Object\Flag.h"
#include "..\DecisionMaking\StateMachine.h"
#include "..\DecisionMaking\AttackState.h"
#include "..\DecisionMaking\GrabState.h"
#include "..\DecisionMaking\DefendState.h"

class AIManager
{
private:
	//World inputs used for decision making
	Flag* flag;
	Pacman* pacman;
	Ghost* ghost[3];
public:
	StateMachine* StateMachines[4];
public:
	AIManager() { }
	~AIManager();
	void InitAI();
	void ControlAIActors();
};
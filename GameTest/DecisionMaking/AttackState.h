#pragma once
#include "StateMachine.h"

class AttackState : public State
{
public:
	AttackState(StateMachine* stateMachine) : State(stateMachine) { _stateType = EStates::Attack; _stateMachine = stateMachine; }
	~AttackState() { }
	void Action() override;
	std::tuple<MapTileObject*, MapTileObject*> DetermineMovement(bool isPacman) override;
	void Move(MapTileObject* current, MapTileObject* destination, bool isPacman) override;
};
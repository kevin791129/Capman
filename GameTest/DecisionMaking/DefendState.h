#pragma once
#include "StateMachine.h"

class DefendState : public State
{
private:
	bool isGhostFlagHolder = false;
	int ghostFlagHolder = 0;
	float pacmanClosestGhostDist = 0.0f;
	int pacmanClosestGhostIndex = 0;
public:
	DefendState(StateMachine* stateMachine) : State(stateMachine) { _stateType = EStates::Defend; _stateMachine = stateMachine; }
	~DefendState() { }
	void Action() override;
	std::tuple<MapTileObject*, MapTileObject*> DetermineMovement(bool isPacman) override;
	void Move(MapTileObject* current, MapTileObject* destination, bool isPacman) override;
	int MoveAwayDirection(MapTileObject* current, MapTileObject* target);
};
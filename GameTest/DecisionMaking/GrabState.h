#pragma once
#include "StateMachine.h"

class GrabState : public State
{
private:
	//Ghost variables
	bool ghostTooClose = false;
	int closestGhostIndex;
public:
	GrabState(StateMachine* stateMachine) : State(stateMachine) { _stateType = EStates::Grab; _stateMachine = stateMachine; }
	~GrabState() { }
	void Action() override;
	std::tuple<MapTileObject*, MapTileObject*> DetermineMovement(bool isPacman) override;
	void Move(MapTileObject* current, MapTileObject* destination, bool isPacman) override;
	int Wander(const int row, const int col, const int lastDir);
};
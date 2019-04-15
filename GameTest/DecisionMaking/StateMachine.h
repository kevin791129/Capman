#pragma once
#include "..\Utility.h"
#include "..\Object\Pacman.h"
#include "..\Object\Ghost.h"
#include "..\Object\Flag.h"
#include "..\TileMap.h"
#include "..\Manager\GameManager.h"
#include "..\Object\Movable.h"

class StateMachine;

class State
{
protected:
	StateMachine * _stateMachine;
	Movable* moveComponent;
public:
	EStates _stateType;
public:
	State(StateMachine* stateMachine) : _stateMachine(stateMachine) { }
	~State() { }
	virtual void Action() = 0;
	virtual std::tuple<MapTileObject*, MapTileObject*> DetermineMovement(bool isPacman) = 0;
	virtual void Move(MapTileObject* current, MapTileObject* destination, bool isPacman) = 0;
	MapTileObject* GetMapCorner(Vec2 position, bool isFurthestFromPoint);
	bool CheckPathForType(MapGraphNode* startNode, int peakDist, EActorType enemyType) const;
};

class StateMachine
{
private:
	State* _states[3];
public:
	EStates _currentState;
	Pacman* _pacman;
	Ghost* _ghosts[3];
	Flag* _flag;
	int _self;
	bool _stateChanged;
	int _remainOnPath;
public:
	StateMachine(EStates initState) : _currentState(initState) { }
	~StateMachine();
	void InitStateMachine(const int self, Pacman* p, Ghost* g1, Ghost* g2, Ghost* g3, Flag* f, State* attack, State* grab, State* defend);
	EStates CheckIfChangeState();
	void DoStateAction();
	void SetState(EStates state);
};
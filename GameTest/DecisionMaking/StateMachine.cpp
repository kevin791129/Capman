#include "..\stdafx.h"
#include "StateMachine.h"

StateMachine::~StateMachine()
{
	for (State* state : _states)
	{
		delete state;
	}
}

void StateMachine::InitStateMachine(const int self, Pacman* p, Ghost* g1, Ghost* g2, Ghost* g3, Flag* f, State* attack, State* grab, State* defend)
{
	_self = self;
	_pacman = p;
	_ghosts[0] = g1;
	_ghosts[1] = g2;
	_ghosts[2] = g3;
	_flag = f;
	_states[0] = attack;
	_states[1] = grab;
	_states[2] = defend;
}

EStates StateMachine::CheckIfChangeState()
{
	if (_flag->_isHeld)
	{
		if (_flag->_owner->_type == EActorType::EPacman && _self == 0)
		{
			return EStates::Defend;
		}
		else if (_flag->_owner->_type == EActorType::EGhost && _self != 0)
		{
			return EStates::Defend;
		}
		else
		{
			return EStates::Attack;
		}
	}
	else
	{
		return EStates::Grab;
	}
}

void StateMachine::DoStateAction()
{
	_states[_currentState]->Action();
}

void StateMachine::SetState(EStates state)
{
	_stateChanged = _currentState != state;
	_currentState = state;
}

MapTileObject* State::GetMapCorner(Vec2 position, bool isFurthestFromPoint)
{
	MapTileObject* corners[4];
	corners[0] = GameManager::Map->GetTile(1, 1);
	corners[1] = GameManager::Map->GetTile(1, 30);
	corners[2] = GameManager::Map->GetTile(22, 1);
	corners[3] = GameManager::Map->GetTile(21, 30);
	Vec2 posi[4];
	float diffs[4];
	for (int i = 0; i < 4; i++)
	{
		posi[i] = corners[i]->_position;
		diffs[i] = (posi[i] - position).Length();
	}
	if (isFurthestFromPoint)
	{
		int largestIndex = -1;
		int largestDist = 0.0f;
		for (int j = 0; j < 4; j++)
		{
			if (diffs[j] > largestDist)
			{
				largestIndex = j;
				largestDist = diffs[j];
			}
		}
		return corners[largestIndex];
	}
	else
	{
		int smallestIndex = -1;
		int smallestDist = 100.0f;
		for (int j = 0; j < 4; j++)
		{
			if (diffs[j] < smallestDist)
			{
				smallestIndex = j;
				smallestDist = diffs[j];
			}
		}
		return corners[smallestIndex];
	}
}

bool State::CheckPathForType(MapGraphNode* startNode, int peakDist, EActorType type) const
{
	MapGraphNode* current = startNode;
	int seekCount = peakDist;
	bool rePath = false;
	while (seekCount > 0 && current->_nextNode != nullptr)
	{
		if (type == EActorType::EPacman)
		{
			if (_stateMachine->_pacman->_currentTile == current->_mapTile)
			{
				rePath = true;
				break;
			}
		}
		else if (type == EActorType::EGhost)
		{
			for (int i = 0; i < 3; i++)
			{
				if (_stateMachine->_ghosts[i]->_currentTile == current->_mapTile)
				{
					rePath = true;
					break;
				}
			}
		}
		seekCount--;
		current = current->_nextNode;
	}
	return false;
}

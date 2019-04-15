#include "..\stdafx.h"
#include "GrabState.h"

void GrabState::Action()
{
	//Set moveComponent if not set
	if (moveComponent == nullptr)
	{
		if (_stateMachine->_self == 0)
		{
			moveComponent = dynamic_cast<Movable*>(_stateMachine->_pacman);
		}
		else
		{
			moveComponent = dynamic_cast<Movable*>(_stateMachine->_ghosts[_stateMachine->_self - 1]);
		}
	}

	std::tuple<MapTileObject*, MapTileObject*> StartEndTiles = DetermineMovement(_stateMachine->_self == 0);
	Move(std::get<0>(StartEndTiles), std::get<1>(StartEndTiles), _stateMachine->_self == 0);
}

std::tuple<MapTileObject*, MapTileObject*> GrabState::DetermineMovement(bool isPacman)
{
	MapTileObject* currentTile = nullptr;
	MapTileObject* destTile = nullptr;
	if (isPacman)
	{
		currentTile = _stateMachine->_pacman->_currentTile;
		destTile = GameManager::Map->GetTile(_stateMachine->_flag->_mapRow, _stateMachine->_flag->_mapCol);
	}
	else
	{
		//Reset variables
		ghostTooClose = false;
		closestGhostIndex = -1;
		//Set current tile
		currentTile = _stateMachine->_ghosts[_stateMachine->_self - 1]->_currentTile;
		Vec2 flagDiff = _stateMachine->_flag->_position;
		flagDiff -= _stateMachine->_ghosts[_stateMachine->_self - 1]->_position;
		//If flag is within visible range, flag is destination tile
		if (flagDiff.Length() < 13.0f)
		{
			destTile = GameManager::Map->GetTile(_stateMachine->_flag->_mapRow, _stateMachine->_flag->_mapCol);
		}
		//If close to other ghosts, destination tile not determined yet
		else
		{
			Vec2 gOtherDiff;
			Vec2 gOther2Diff;
			if (_stateMachine->_self == 1)
			{
				gOtherDiff = _stateMachine->_ghosts[1]->_position;
				gOther2Diff = _stateMachine->_ghosts[2]->_position;
				gOtherDiff -= _stateMachine->_ghosts[0]->_position;
				gOther2Diff -= _stateMachine->_ghosts[0]->_position;
				if (gOtherDiff.Length() < 3.0f)
				{
					ghostTooClose = true;
					closestGhostIndex = 1;
				}
				else if (gOther2Diff.Length() < 3.0f)
				{
					ghostTooClose = true;
					closestGhostIndex = 2;
				}
			}
			else if (_stateMachine->_self == 2)
			{
				gOtherDiff = _stateMachine->_ghosts[0]->_position;
				gOther2Diff = _stateMachine->_ghosts[2]->_position;
				gOtherDiff -= _stateMachine->_ghosts[1]->_position;
				gOther2Diff -= _stateMachine->_ghosts[1]->_position;
				if (gOtherDiff.Length() < 3.0f)
				{
					ghostTooClose = true;
					closestGhostIndex = 0;
				}
				else if (gOther2Diff.Length() < 3.0f)
				{
					ghostTooClose = true;
					closestGhostIndex = 2;
				}
			}
			else
			{
				gOtherDiff = _stateMachine->_ghosts[0]->_position;
				gOther2Diff = _stateMachine->_ghosts[1]->_position;
				gOtherDiff -= _stateMachine->_ghosts[2]->_position;
				gOther2Diff -= _stateMachine->_ghosts[2]->_position;
				if (gOtherDiff.Length() < 3.0f)
				{
					ghostTooClose = true;
					closestGhostIndex = 0;
				}
				else if (gOther2Diff.Length() < 3.0f)
				{
					ghostTooClose = true;
					closestGhostIndex = 1;
				}
			}
		}
	}
	return std::make_tuple(currentTile, destTile);
}

void GrabState::Move(MapTileObject* current, MapTileObject* destination, bool isPacman)
{
	if (moveComponent == nullptr || !moveComponent->_takeMoveInput)
		return;

	if (_stateMachine->_stateChanged)
	{
		moveComponent->FreePath();
	}
	else if (_stateMachine->_remainOnPath > 0 && moveComponent->_current != nullptr)
	{
		_stateMachine->_remainOnPath--;
		moveComponent->TraversePath();
		return;
	}

	if (isPacman)
	{
		if (current != nullptr && destination != nullptr)
		{
			moveComponent->FreePath();
			moveComponent->_pathStart = GameManager::Map->Pathfind(current, destination);
		}
		moveComponent->TraversePath();
	}
	else
	{
		//If destination is set, set path to destination
		if (current != nullptr && destination != nullptr)
		{
			moveComponent->FreePath();
			moveComponent->_pathStart = GameManager::Map->Pathfind(current, destination);
			_stateMachine->_remainOnPath = 10;
			moveComponent->TraversePath();
			return;
		}
		else
		{
			if (ghostTooClose)
			{
				MapTileObject* destTile;
				//Smaller index ghost go to nearest corner, larger index ghost go to furthest corner
				if (_stateMachine->_self < closestGhostIndex + 1)
				{
					destTile = GetMapCorner(_stateMachine->_ghosts[closestGhostIndex]->_position, false);
					_stateMachine->_remainOnPath = 7;
				}
				else
				{
					destTile = GetMapCorner(_stateMachine->_ghosts[closestGhostIndex]->_position, true);
					_stateMachine->_remainOnPath = 16;
				}
				moveComponent->FreePath();
				moveComponent->_pathStart = GameManager::Map->Pathfind(current, destTile);
				moveComponent->TraversePath();
				return;
			}
			else
			{
				//Wander randomly without back-tracking
				int wanderDir = Wander(current->_mapRow, current->_mapCol, moveComponent->_lastDir);
				moveComponent->StartMove(wanderDir);
				return;
			}
		}
	}
}

int GrabState::Wander(const int row, const int col, int lastDir)
{
	int wanderDir;
	switch (lastDir)
	{
	case 0:
		wanderDir = GameManager::Map->GetPossibleRandomNextDirection(row, col, 2);
		break;
	case 1:
		wanderDir = GameManager::Map->GetPossibleRandomNextDirection(row, col, 3);
		break;
	case 2:
		wanderDir = GameManager::Map->GetPossibleRandomNextDirection(row, col, 0);
		break;
	case 3:
		wanderDir = GameManager::Map->GetPossibleRandomNextDirection(row, col, 1);
		break;
	default:
		wanderDir = GameManager::Map->GetPossibleRandomNextDirection(row, col);
		break;
	}
	return wanderDir;
}

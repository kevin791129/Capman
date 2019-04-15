#include "..\stdafx.h"
#include "DefendState.h"

void DefendState::Action()
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

std::tuple<MapTileObject*, MapTileObject*> DefendState::DetermineMovement(bool isPacman)
{
	MapTileObject* currentTile = nullptr;
	MapTileObject* destTile = nullptr;
	if (isPacman)
	{
		currentTile = _stateMachine->_pacman->_currentTile;
		//Find closest ghost and move away from it
		pacmanClosestGhostIndex = -1;
		pacmanClosestGhostDist = 100.0f;
		for (int i = 0; i < 3; i++)
		{
			Vec2 currentPosi = _stateMachine->_pacman->_position;
			Vec2 ghostPosi = _stateMachine->_ghosts[i]->_position;
			float dist = (ghostPosi - currentPosi).Length();
			if (dist < pacmanClosestGhostDist)
			{
				pacmanClosestGhostDist = dist;
				pacmanClosestGhostIndex = i;
			}
		}
		if (pacmanClosestGhostDist < 4.0f)
		{

		}
		else
		{
			destTile = GetMapCorner(_stateMachine->_ghosts[pacmanClosestGhostIndex]->_position, true);
		}
	}
	else
	{
		currentTile = _stateMachine->_ghosts[_stateMachine->_self - 1]->_currentTile;
		for (int i = 0; i < 3; i++)
		{
			if (_stateMachine->_flag->_owner == _stateMachine->_ghosts[i])
			{
				ghostFlagHolder = i + 1;
				isGhostFlagHolder = _stateMachine->_self == ghostFlagHolder;
				break;
			}
		}

		if (isGhostFlagHolder)
		{
			destTile = GetMapCorner(_stateMachine->_pacman->_position, true);
		}
		else
		{
			destTile = _stateMachine->_pacman->_currentTile;
		}
	}
	return std::make_tuple(currentTile, destTile);
}

void DefendState::Move(MapTileObject* current, MapTileObject* destination, bool isPacman)
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
		if (pacmanClosestGhostDist < 4.0f)
		{
			int doGoDir = MoveAwayDirection(current, _stateMachine->_ghosts[pacmanClosestGhostIndex]->_currentTile);
			moveComponent->FreePath();
			moveComponent->_pathStart = GameManager::Map->FindRandomPathToNextIntersection(current, doGoDir);
			_stateMachine->_remainOnPath = 3;
			moveComponent->TraversePath();
			return;
		}
		else
		{
			moveComponent->FreePath();
			moveComponent->_pathStart = GameManager::Map->Pathfind(current, destination, moveComponent->_lastDir);
			int pathDir = GameManager::Map->FindNextDirectionInPath(moveComponent->_pathStart);
			if (CheckPathForType(moveComponent->_pathStart, 7, EActorType::EGhost))
			{
				moveComponent->FreePath();
				moveComponent->_pathStart = GameManager::Map->Pathfind(current, destination, pathDir);
			}
			_stateMachine->_remainOnPath = 5;
			moveComponent->TraversePath();
			return;
		}
	}
	else
	{
		if (isGhostFlagHolder)
		{
			//Runaway from pacman
			if (current != nullptr && destination != nullptr && current != destination)
			{
				moveComponent->FreePath();
				moveComponent->_pathStart = GameManager::Map->Pathfind(current, destination, moveComponent->_lastDir);
				int pathDir = GameManager::Map->FindNextDirectionInPath(moveComponent->_pathStart);
				bool rePath = CheckPathForType(moveComponent->_pathStart, 7, EActorType::EPacman);
				if (rePath)
				{
					moveComponent->FreePath();
					moveComponent->_pathStart = GameManager::Map->Pathfind(current, destination, pathDir);
				}
				_stateMachine->_remainOnPath = 6;
				moveComponent->TraversePath();
				return;
			}
		}
		else
		{
			//Other 2 ghost go protect the flag holding ghost
			if (current != nullptr && destination != nullptr && current != destination)
			{
				moveComponent->FreePath();
				moveComponent->_pathStart = GameManager::Map->Pathfind(current, destination, moveComponent->_lastDir);
			}
			else
			{
				moveComponent->_pathStart = GameManager::Map->FindRandomPathToNextIntersection(current, moveComponent->_lastDir);
			}
			_stateMachine->_remainOnPath = 6;
			moveComponent->TraversePath();
			return;
		}
	}

	if (moveComponent->_pathStart == nullptr)
	{
		int moveDir = GameManager::Map->GetPossibleWithFavourDirection(current->_mapRow, current->_mapCol, moveComponent->_lastDir);
		moveComponent->StartMove(moveDir);
		return;
	}
	moveComponent->TraversePath();
}

int DefendState::MoveAwayDirection(MapTileObject* current, MapTileObject* target)
{
	MapGraphNode* pathStart = GameManager::Map->Pathfind(current, target);
	if (pathStart != nullptr)
	{
		int moveDir = GameManager::Map->FindNextDirectionInPath(pathStart);
		//Path clean up
		MapGraphNode* currentNode = pathStart->GetPathEnd();
		while (currentNode->_previousNode != nullptr)
		{
			currentNode = currentNode->_previousNode;
			delete currentNode->_nextNode;
		}
		delete currentNode;
		pathStart = nullptr;
		return GameManager::Map->GetPossibleRandomNextDirection(current->_mapRow, current->_mapCol, moveDir);
	}
	return GameManager::Map->GetPossibleRandomNextDirection(current->_mapRow, current->_mapCol);
}

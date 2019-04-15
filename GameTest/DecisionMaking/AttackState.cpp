#include "..\stdafx.h"
#include "AttackState.h"

void AttackState::Action()
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

std::tuple<MapTileObject*, MapTileObject*> AttackState::DetermineMovement(bool isPacman)
{
	MapTileObject* currentTile = nullptr;
	MapTileObject* destTile = nullptr;
	if (isPacman)
	{
		currentTile = _stateMachine->_pacman->_currentTile;
		if (GameManager::CoinsCollected > GameManager::CoinLoseAmount)
		{
			//If has enough coins chase after flag
			for (int i = 0; i < 3; i++)
			{
				if (_stateMachine->_ghosts[i] == _stateMachine->_flag->_owner)
				{
					destTile = _stateMachine->_ghosts[i]->_currentTile;
					break;
				}
			}
		}
		else
		{

		}
	}
	else
	{
		currentTile = _stateMachine->_ghosts[_stateMachine->_self - 1]->_currentTile;
		destTile = _stateMachine->_pacman->_currentTile;
	}
	return std::make_tuple(currentTile, destTile);
}

void AttackState::Move(MapTileObject* current, MapTileObject* destination, bool isPacman)
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
			moveComponent->TraversePath();
			return;
		}
		else
		{
			//If has path to coin, peek ahead for ghosts
			if (moveComponent->_pathStart != nullptr)
			{
				if (CheckPathForType(moveComponent->_pathStart, 4, EActorType::EGhost))
				{
					int pathDir = GameManager::Map->FindNextDirectionInPath(moveComponent->_pathStart);
					moveComponent->FreePath();
					moveComponent->_pathStart = GameManager::Map->FindRandomPathToNextIntersection(_stateMachine->_pacman->_currentTile, pathDir);
					_stateMachine->_remainOnPath = 4;
					moveComponent->TraversePath();
					return;
				}
			}
			//No destination, choose random coin as destination
			if (GameManager::ActorList->size() - 5 > 0)
			{
				int randCoinIndex = IRAND_RANGE(0, GameManager::ActorList->size() - 5);
				MapTileObject* destTile = GameManager::Map->GetTile(GameManager::ActorList->at(randCoinIndex)->_position._y, GameManager::ActorList->at(randCoinIndex)->_position._x);
				moveComponent->_pathStart = GameManager::Map->Pathfind(current, destTile);
			}
			else
			{
				moveComponent->_pathStart = GameManager::Map->FindRandomPathToNextIntersection(_stateMachine->_pacman->_currentTile, moveComponent->_lastDir);
			}
			//Peek ahead after choosing a path
			if (CheckPathForType(moveComponent->_pathStart, 4, EActorType::EGhost))
			{
				int pathDir = GameManager::Map->FindNextDirectionInPath(moveComponent->_pathStart);
				moveComponent->FreePath();
				moveComponent->_pathStart = GameManager::Map->FindRandomPathToNextIntersection(_stateMachine->_pacman->_currentTile, pathDir);
				_stateMachine->_remainOnPath = 4;
			}
			else
			{
				moveComponent->TraversePath();
				return;
			}
		}
	}
	else
	{
		//Ghost cannot move backwards, so re-path can only happen at a tile with more than 2 connects or at end of path
		if (GameManager::Map->GetTileNumConnections(current) >= 3 || moveComponent->_pathStart == nullptr)
		{
			if (current != nullptr && destination != nullptr)
			{
				moveComponent->FreePath();
				switch (moveComponent->_lastDir)
				{
				case 0:
					moveComponent->_pathStart = GameManager::Map->Pathfind(current, destination, 2);
					break;
				case 1:
					moveComponent->_pathStart = GameManager::Map->Pathfind(current, destination, 3);
					break;
				case 2:
					moveComponent->_pathStart = GameManager::Map->Pathfind(current, destination, 0);
					break;
				case 3:
					moveComponent->_pathStart = GameManager::Map->Pathfind(current, destination, 1);
					break;
				default:
					moveComponent->_pathStart = GameManager::Map->Pathfind(current, destination);
					break;
				}
				//_stateMachine->_remainOnPath = IRAND_RANGE(3, 10);
				moveComponent->TraversePath();
				return;
			}
		}
		moveComponent->TraversePath();
		return;
	}
}
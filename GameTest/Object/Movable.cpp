#include "..\stdafx.h"
#include "Movable.h"
#include "..\TileMap.h"

Movable::~Movable()
{
	FreePath();
}

void Movable::StartMove(int dir)
{
	if (_takeMoveInput && _currentTile != nullptr)
	{
		_lerpTime = 0.0f;
		int nextRow = _currentTile->_mapRow + (int)directions[dir][0];
		int nextCol = _currentTile->_mapCol + (int)directions[dir][1];
		if (_currentTile->_map->GetMapTileType(nextRow, nextCol) == EMapTileType::Floor)
		{
			_nextTile = _currentTile->_map->GetTile(nextRow, nextCol);
			_takeMoveInput = false;
			_lastDir = dir;
		}
	}
}

void Movable::Freeze(float time)
{
	_freezeTime = time;
	_noFreezeTime = time + 2.0f;
}

void Movable::TraversePath()
{
	if (_pathStart == nullptr)
		return;

	if (_current == nullptr)
		_current = _pathStart;

	if (_current->_nextNode != nullptr)
	{
		int row = _current->_nextNode->_mapTile->_mapRow - _current->_mapTile->_mapRow;
		int col = _current->_nextNode->_mapTile->_mapCol - _current->_mapTile->_mapCol;
		if (row == 1 && col == 0)
			StartMove(0);
		else if (row == 0 && col == 1)
			StartMove(1);
		else if (row == -1 && col == 0)
			StartMove(2);
		else if (row == 0 && col == -1)
			StartMove(3);
		_current = _current->_nextNode;
	}
	else
	{
		FreePath();
	}
}

void Movable::FreePath()
{
	if (_pathStart != nullptr)
	{
		MapGraphNode* current = _pathStart->GetPathEnd();
		while (current->_previousNode != nullptr)
		{
			current = current->_previousNode;
			delete current->_nextNode;
		}
		delete current;
		_pathStart = nullptr;
	}
	_current = nullptr;
}

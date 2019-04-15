#pragma once
#include "MapTileObject.h"
#include "BaseObject.h"
#include "..\TileMap.h"

class Movable
{
public:
	float _freezeTime;
	float _noFreezeTime;
	float _lerpTime;
	float _speed;
	bool _takeMoveInput;
	int _lastDir;
	MapTileObject* _currentTile;
	MapTileObject* _nextTile;
	MapGraphNode* _pathStart;
	MapGraphNode* _current;
public:
	Movable() { }
	~Movable();
	void StartMove(int dir);
	void Freeze(float time = 3.0f);
	void TraversePath();
	void FreePath();
	virtual void Move(float deltaTime) = 0;
};
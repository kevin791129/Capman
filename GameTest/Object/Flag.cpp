#include "..\stdafx.h"
#include "Flag.h"
#include "..\Manager\GameManager.h"
#include "Pacman.h"
#include "Ghost.h"

Flag::Flag(MapTileObject* tile) : _isHeld(false), _owner(nullptr), _mapRow(tile->_mapRow), _mapCol(tile->_mapCol)
{
	_type = EActorType::EFlag;
	SetPosition(tile->_position._x, tile->_position._y);
	_radius = 0.2f;
}

void Flag::UpdateObject(float deltaTime)
{
	if (_isHeld)
	{
		Pacman* p = dynamic_cast<Pacman*>(_owner);
		Ghost* g = dynamic_cast<Ghost*>(_owner);
		if (p != nullptr)
		{
			GameManager::PacmanFlagScore += deltaTime / 200.0f;
		}
		else if (g != nullptr)
		{
			GameManager::GhostFlagScore += deltaTime / 200.0f;
		}
		SetPosition(_owner->_position._x, _owner->_position._y);
	}
}

void Flag::DrawObject() const
{
	float x = _position._x;
	float y = _position._y;
	float r = TILE_WIDTH * _radius;
	MAP_COORD_TO_VIR_COORD(x, y);
	App::DrawNgon(x, y, r, 0.0f, 360.0f, 0.3f, 0.5f, 0.6f, 3);
}

void Flag::ResolveCollision(const EActorType otherType, ActorObject* otherActor)
{
	Movable* move = dynamic_cast<Movable*>(otherActor);
	if (move != nullptr && move->_freezeTime > 0.0f)
		return;

	if (_isHeld)
	{
		return;
	}
	else
	{
		Pickup(otherActor);
	}
}

void Flag::Pickup(ActorObject * owner)
{
	_isHeld = true;
	_owner = owner;
}

void Flag::Drop()
{
	_isHeld = false;
	_owner = nullptr;
	EMapTileType spawnTileType = EMapTileType::Wall;
	do
	{
		_mapRow = IRAND_RANGE(1, mapSizeY);
		_mapCol = IRAND_RANGE(1, mapSizeX);
		spawnTileType = GameManager::Map->GetMapTileType(_mapRow, _mapCol);
	} while (spawnTileType <= EMapTileType::Wall);
	SetPosition(GameManager::Map->GetTile(_mapRow, _mapCol)->_position._x, GameManager::Map->GetTile(_mapRow, _mapCol)->_position._y);
}

#include "..\stdafx.h"
#include "Ghost.h"
#include "..\Manager\GameManager.h"
#include "Flag.h"

Ghost::Ghost(MapTileObject* tile, float r, float g, float b) : _r(r), _g(g), _b(b)
{
	_type = EActorType::EGhost;
	_currentTile = tile;
	SetPosition(_currentTile->_position._x, _currentTile->_position._y);
	_radius = 0.35f;
	_speed = 5.0f;
	_takeMoveInput = true;
}

void Ghost::UpdateObject(float deltaTime)
{
	_noFreezeTime -= deltaTime / 1000.0f;
	if (_freezeTime > 0.0f)
	{
		_freezeTime -= deltaTime / 1000.0f;
	}
	else
	{
		Move(deltaTime);
	}
}

void Ghost::DrawObject() const
{
	float x = _position._x;
	float y = _position._y;
	float r = TILE_WIDTH * _radius;
	MAP_COORD_TO_VIR_COORD(x, y);
	App::DrawNgon(x, y, r, 0.0f, 180.0f, _r, _g, _b);
	App::DrawQuad(x - r, y - r, x + r, y, _r, _g, _b);
}

void Ghost::ResolveCollision(const EActorType otherType, ActorObject* otherActor)
{
	Movable* move = dynamic_cast<Movable*>(otherActor);
	if (move != nullptr && move->_freezeTime > 0.0f)
		return;

	if (_freezeTime > 0.0f)
		return;

	if (otherType == EActorType::EPacman)
	{
		if (_noFreezeTime > 0.0f)
			return;

		if (GameManager::CoinsCollected >= GameManager::CoinLoseAmount)
		{
			Freeze();
			Flag* flag = dynamic_cast<Flag*>(GameManager::ActorList->at(GameManager::ActorList->size() - 1));
			if (flag->_isHeld)
			{
				//Flag holder drop flag
				Vec2 diff = flag->_position;
				diff -= _position;
				if (diff.Length() < _radius && flag->_owner->_type == EActorType::EGhost)
				{
					flag->Drop();
				}
			}
		}
	}
}

void Ghost::Move(float deltaTime)
{
	if (!_takeMoveInput && _currentTile != nullptr && _nextTile != nullptr)
	{
		bool flagHolder = false;
		Flag* flag = dynamic_cast<Flag*>(GameManager::ActorList->at(GameManager::ActorList->size() - 1));
		if (flag->_isHeld)
		{
			//Flag holder drop flag
			Vec2 diff = flag->_position;
			diff -= _position;
			flagHolder = diff.Length() < 0.1f && flag->_owner->_type == EActorType::EGhost;
		}

		_lerpTime += flagHolder ? _speed * 0.7f * deltaTime / 1000.0f : _speed * deltaTime / 1000.0f;
		Vec2 posi = Vec2::Lerp(_currentTile->_position, _nextTile->_position, _lerpTime);
		SetPosition(posi._x, posi._y);
		if (_lerpTime >= 1.0f)
		{
			SetPosition(_nextTile->_position._x, _nextTile->_position._y);
			_currentTile = _nextTile;
			_nextTile = nullptr;
			_takeMoveInput = true;
		}
	}
}

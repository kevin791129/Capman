#include "..\stdafx.h"
#include "Pacman.h"
#include "..\Manager\GameManager.h"
#include "..\Manager\GameManager.h"
#include "Flag.h"

Pacman::Pacman(int x, int y) : _mouthOpenAngle(0.0f), _mouthSpeed(30.0f), _mouthOpening(true)
{
	_type = EActorType::EPacman;
	SetPosition((float)y, (float)x);
	_radius = 0.35f;
	_speed = 5.0f;
	_takeMoveInput = true;
}

Pacman::Pacman(MapTileObject* tile) : _mouthOpenAngle(0.0f), _mouthSpeed(30.0f), _mouthOpening(true)
{
	_type = EActorType::EPacman;
	_currentTile = tile;
	SetPosition(_currentTile->_position._x, _currentTile->_position._y);
	_radius = 0.35f;
	_speed = 5.0f;
	_takeMoveInput = true;
}

void Pacman::UpdateObject(float deltaTime)
{
	_noFreezeTime -= deltaTime / 1000.0f;
	if (_freezeTime > 0.0f)
	{
		_freezeTime -= deltaTime / 1000.0f;
	}
	else
	{
		if (_mouthOpening)
		{
			_mouthOpenAngle += _mouthSpeed * deltaTime / 1000.0f;
			if (_mouthOpenAngle >= 30.0f)
			{
				_mouthOpenAngle = 30.0f;
				_mouthOpening = false;
			}
		}
		else
		{
			_mouthOpenAngle -= _mouthSpeed * deltaTime / 1000.0f;
			if (_mouthOpenAngle <= 0.0f)
			{
				_mouthOpenAngle = 0.0f;
				_mouthOpening = true;
			}
		}
		Move(deltaTime);
	}
}

void Pacman::DrawObject() const
{
	float x = _position._x;
	float y = _position._y;
	float r = TILE_WIDTH * _radius;
	MAP_COORD_TO_VIR_COORD(x, y);
	App::DrawNgon(x, y, r, _mouthOpenAngle * 0.5f, 360.0f - _mouthOpenAngle * 0.5f, 0.8f, 0.8f, 0.1f);
}

void Pacman::ResolveCollision(const EActorType otherType, ActorObject* otherActor)
{
	Movable* move = dynamic_cast<Movable*>(otherActor);
	if (move != nullptr && move->_freezeTime > 0.0f)
		return;

	if (_freezeTime > 0.0f)
		return;

	if (otherType == EActorType::ECoins)
	{
		GameManager::IncreaseCoin();
	}
	else if (otherType == EActorType::EGhost)
	{
		if (_noFreezeTime > 0.0f)
			return;

		if (GameManager::CoinsCollected <= GameManager::CoinLoseAmount)
		{
			Freeze();
		}

		GameManager::DecreaseCoin();

		Flag* flag = dynamic_cast<Flag*>(GameManager::ActorList->at(GameManager::ActorList->size() - 1));
		if (flag->_isHeld && flag->_owner->_type == EActorType::EPacman)
		{
			flag->Drop();
		}
	}
}

void Pacman::Move(float deltaTime)
{
	if (!_takeMoveInput && _currentTile != nullptr && _nextTile != nullptr)
	{
		bool flagHolder = false;
		Flag* flag = dynamic_cast<Flag*>(GameManager::ActorList->at(GameManager::ActorList->size() - 1));
		if (flag->_isHeld)
		{
			flagHolder = flag->_owner->_type == EActorType::EPacman;
			if (flagHolder || flag == nullptr)
			{
				int i;
			}
		}

		_lerpTime += flagHolder ? _speed * 0.75f * deltaTime / 1000.0f : _speed * deltaTime / 1000.0f;
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

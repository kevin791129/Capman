#include "..\stdafx.h"
#include "BaseObject.h"

void BaseObject::SetPosition(const float x, const float y)
{
	_position._x = x;
	_position._y = y;
}

void BaseObject::Translate(const Vec2 moveVector)
{
	_position += moveVector;
}

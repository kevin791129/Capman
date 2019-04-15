#include "..\stdafx.h"
#include "Coin.h"

void Coin::UpdateObject(float deltaTime)
{

}

void Coin::DrawObject() const
{
	float x = _position._x;
	float y = _position._y;
	float r = TILE_WIDTH * _radius;
	MAP_COORD_TO_VIR_COORD(x, y);
	App::DrawNgon(x, y, r, 0.0f, 360.0f, 0.7f, 0.7f, 0.2f, 36);
}

void Coin::ResolveCollision(const EActorType otherType, ActorObject* otherActor)
{
	if (otherType == EActorType::EPacman)
	{
		_toBeDestory = true;
	}
}

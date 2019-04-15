#include "..\stdafx.h"
#include "MapTileObject.h"

void MapTileObject::UpdateObject(float deltaTime)
{
	//Stationary object, do nothing
}

void MapTileObject::DrawObject() const
{
	//Only need to draw walls
	if (_tileType > EMapTileType::Wall)
		return;

	float x = _position._x;
	float y = _position._y;
	MAP_COORD_TO_VIR_COORD(x, y);
	float w = TILE_WIDTH * 0.5f;
	float h = TILE_HEIGHT * 0.5f;
	App::DrawQuad(x - w, y - h, x + w, y + h, mapTileColors[1][0], mapTileColors[1][1], mapTileColors[1][2]);
}

EMapTileType MapTileObject::GetMapTileType() const
{
	return _tileType;
}

void MapTileObject::SetMapTileType(const EMapTileType tileType)
{
	_tileType = tileType;
}


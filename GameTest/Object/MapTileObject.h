#pragma once
#include "BaseObject.h"
#include "..\Utility.h"

class TileMap;

class MapTileObject : public BaseObject
{
public:
	int _mapRow;
	int _mapCol;
	TileMap* _map;
private:
	EMapTileType _tileType;
public:
	//--------------------------------------------------------------------------------------------
	// Constructor and functions from parent class
	//--------------------------------------------------------------------------------------------
	MapTileObject(int x, int y, TileMap* map) : _mapRow(x), _mapCol(y), _map(map), _tileType(EMapTileType::Floor) { SetPosition((float)y, (float)x); }
	~MapTileObject() override { }
	void MapTileObject::UpdateObject(float deltaTime) override;
	void MapTileObject::DrawObject() const override;
	//--------------------------------------------------------------------------------------------
	// Setter and getter for tile type
	//--------------------------------------------------------------------------------------------
	EMapTileType GetMapTileType() const;
	void SetMapTileType(const EMapTileType tileType);
};
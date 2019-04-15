#ifndef _UTILITY_H
#define _UTILITY_H

#include "..\GameTest\App\app.h"

const int mapSizeX = 32;
const int mapSizeY = 24;

#define MAP_COORD_TO_VIR_COORD(_x_, _y_)			_x_ = (APP_VIRTUAL_WIDTH / mapSizeX) * (_x_ + 0.5f); _y_ = (APP_VIRTUAL_HEIGHT / mapSizeY) * (_y_ + 0.5f);
#define TILE_WIDTH (APP_VIRTUAL_WIDTH / mapSizeX)
#define TILE_HEIGHT (APP_VIRTUAL_HEIGHT / mapSizeY)

enum EActorType
{
	ENoCollision = 0,
	EPacman,
	EGhost,
	ECoins,
	EFlag
};

static bool collisionMatrix[5][5] = { { false, false, false, false, false },
{ false, false, true, true, true },
{ false, true, true, false, true },
{ false, true, false, false, false },
{ false, true, true, false, false } };

static const int numOfMapTileTypes = 4;

enum EMapTileType
{
	OutOfBounds = -1,
	Wall,
	Floor,
	Pipe
};

static float mapTileColors[numOfMapTileTypes][3] = { { 0.0f, 0.0f, 0.5f },
{ 0.0f, 0.0f, 0.5f },
{ 0.0f, 0.0f, 0.0f },
{ 0.0f, 0.0f, 0.0f } };

static float directions[4][2] = { { 1.0f, 0.0f },
{ 0.0f, 1.0f },
{ -1.0f, 0.0f },
{ 0.0f, -1.0f } };

static bool mapUnit[5][7] = { {false, false, false, true, true, false, false},
{ false, true, false, false, true, true, true },
{ false, true, true, false, false, false, false } ,
{ false, true, false, false, true, true, true } ,
{ false, true, false, true, true, false, true } };

enum EStates
{
	Attack = 0,
	Grab,
	Defend
};

#endif //_UTILITY_H
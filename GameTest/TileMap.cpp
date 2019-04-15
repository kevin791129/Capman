#include "stdafx.h"
#include "TileMap.h"
#include "Object\Coin.h"

TileMap::TileMap()
{
	CreateMap();
}

TileMap::~TileMap()
{
	for (int row = 0; row < mapSizeY; row++)
	{
		for (int col = 0; col < mapSizeX; row++)
		{
			delete map[row][col];
		}
		map[row].clear();
	}
	map.clear();
}

ActorList TileMap::ResetMap()
{
	ActorList spawnedActors;
	//Set boarder 4 walls
	for (int row = 0; row < mapSizeY; row++)
	{
		map[row][0]->SetMapTileType(EMapTileType::Wall);
		map[row][mapSizeX - 1]->SetMapTileType(EMapTileType::Wall);
	}
	for (int col = 1; col < mapSizeX - 1; col++)
	{
		map[0][col]->SetMapTileType(EMapTileType::Wall);
		map[mapSizeY - 1][col]->SetMapTileType(EMapTileType::Wall);
	}
	//Hardcoded map
	for (int i = 1; i <= 12; i += 11)
	{
		for (int j = 1; j <= 16; j += 15)
		{
			SetSubRegion(i, j, false, false);
			SetSubRegion(i, j + 7, false, true);
			SetSubRegion(i + 5, j, true, false);
			SetSubRegion(i + 5, j + 7, true, true);
		}
	}
	//Map tweaks
	for (int i = 1; i <= 12; i += 11)
	{
		for (int j = 1; j <= 16; j += 15)
		{
			//4-fold mirror mods
			map[i + 1][j + 5]->SetMapTileType(EMapTileType::Floor);
			map[i + 1][j + 7]->SetMapTileType(EMapTileType::Wall);
			map[i + 1][j + 9]->SetMapTileType(EMapTileType::Floor);
			map[i + 5][j + 5]->SetMapTileType(EMapTileType::Floor);
			map[i + 5][j + 6]->SetMapTileType(EMapTileType::Wall);
			map[i + 5][j + 7]->SetMapTileType(EMapTileType::Wall);
			map[i + 5][j + 8]->SetMapTileType(EMapTileType::Wall);
			map[i + 5][j + 9]->SetMapTileType(EMapTileType::Floor);
			map[i + 6][j + 6]->SetMapTileType(EMapTileType::Floor);
			map[i + 4][j + 6]->SetMapTileType(EMapTileType::Floor);
			map[i + 6][j + 8]->SetMapTileType(EMapTileType::Floor);
			map[i + 4][j + 8]->SetMapTileType(EMapTileType::Floor);

			//2-fold horizontally mirror mods
			if (i == 1)
			{
				map[11][j + 1]->SetMapTileType(EMapTileType::Wall);
				map[12][j + 6]->SetMapTileType(EMapTileType::Wall);
				map[12][j + 8]->SetMapTileType(EMapTileType::Wall);
				map[12][j + 13]->SetMapTileType(EMapTileType::Wall);
				map[21][j + 2]->SetMapTileType(EMapTileType::Wall);
				map[10][j + 12]->SetMapTileType(EMapTileType::Wall);
				map[22][j + 12]->SetMapTileType(EMapTileType::Wall);
				map[21][j + 13]->SetMapTileType(EMapTileType::Floor);
				map[22][j + 13]->SetMapTileType(EMapTileType::Wall);
			}
		}
	}
	//1 time only mods and last overrides
	map[13][8]->SetMapTileType(EMapTileType::Floor);
	map[13][23]->SetMapTileType(EMapTileType::Floor);
	map[22][30]->SetMapTileType(EMapTileType::Wall);
	map[20][15]->SetMapTileType(EMapTileType::Wall);
	map[20][16]->SetMapTileType(EMapTileType::Wall);
	map[21][16]->SetMapTileType(EMapTileType::Wall);
	map[21][17]->SetMapTileType(EMapTileType::Floor);
	map[20][17]->SetMapTileType(EMapTileType::Floor);
	map[19][17]->SetMapTileType(EMapTileType::Floor);
	map[17][14]->SetMapTileType(EMapTileType::Wall);
	map[18][16]->SetMapTileType(EMapTileType::Wall);
	map[16][16]->SetMapTileType(EMapTileType::Wall);
	map[13][15]->SetMapTileType(EMapTileType::Wall);
	map[14][15]->SetMapTileType(EMapTileType::Wall);
	map[11][16]->SetMapTileType(EMapTileType::Wall);
	map[9][15]->SetMapTileType(EMapTileType::Wall);
	map[7][16]->SetMapTileType(EMapTileType::Wall);
	map[5][15]->SetMapTileType(EMapTileType::Wall);
	map[5][16]->SetMapTileType(EMapTileType::Wall);
	map[4][14]->SetMapTileType(EMapTileType::Floor);
	map[3][15]->SetMapTileType(EMapTileType::Wall);
	map[2][15]->SetMapTileType(EMapTileType::Wall);
	map[11][17]->SetMapTileType(EMapTileType::Wall);
	map[5][9]->SetMapTileType(EMapTileType::Wall);
	map[19][23]->SetMapTileType(EMapTileType::Wall);
	map[11][22]->SetMapTileType(EMapTileType::Wall);
	map[11][4]->SetMapTileType(EMapTileType::Wall);
	map[11][5]->SetMapTileType(EMapTileType::Wall);
	map[7][22]->SetMapTileType(EMapTileType::Wall);
	map[10][18]->SetMapTileType(EMapTileType::Wall);
	map[10][19]->SetMapTileType(EMapTileType::Wall);
	map[8][21]->SetMapTileType(EMapTileType::Floor);
	map[4][10]->SetMapTileType(EMapTileType::Floor);

	for (int row = 0; row < mapSizeY; row++)
	{
		for (int col = 0; col < mapSizeX; col++)
		{
			if (GetMapTileType(row, col) == EMapTileType::Floor)
			{
				spawnedActors.push_back(new Coin(row, col));
			}
		}
	}
	return spawnedActors;
}

void TileMap::Render() const
{
	for (int row = 0; row < mapSizeY; row++)
	{
		for (int col = 0; col < mapSizeX; col++)
		{
			map[row][col]->DrawObject();
		}
	}
}

EMapTileType TileMap::GetMapTileType(const int row, const int col) const
{
	if (row >= 0 && row < mapSizeY && col >= 0 && col < mapSizeX)
	{
		return map[row][col]->GetMapTileType();
	}
	else
	{
		return EMapTileType::OutOfBounds;
	}
}

EMapTileType TileMap::GetMapTileType(const MapTileObject* tile) const
{
	if (tile != nullptr)
	{
		return tile->GetMapTileType();
	}
	else
	{
		return EMapTileType::OutOfBounds;
	}
}

int TileMap::GetPossibleRandomNextDirection(const int row, const int col, const int exclude) const
{
	std::vector<int> possibleReturns;
	for (int dir = 0; dir < 4; dir++)
	{
		if (dir == exclude)
		{
			continue;
		}

		MapTileObject* next = GetTileInDirection(row, col, dir);
		if (GetMapTileType(next) > EMapTileType::Wall)
		{
			possibleReturns.push_back(dir);
		}
	}
	if (possibleReturns.size() > 0)
	{
		return possibleReturns[IRAND_RANGE(0, possibleReturns.size())];
	}
	return exclude;
}

MapTileObject* TileMap::GetTile(const int x, const int y) const
{
	if (x >= 0 && x < mapSizeY && y >= 0 && y < mapSizeX)
		return map[x][y];
	return nullptr;
}

MapGraphNode* TileMap::Pathfind(MapTileObject* start, MapTileObject* end, int excludeStartDir)
{
	nodes.clear();
	neighbours.clear();

	if (start == end)
		return nullptr;

	//Create start node and surrounding tiles
	MapGraphNode* startNode = new MapGraphNode(start);
	nodes.push_back(startNode);
	PathfindingGetNeighbours(startNode, end, excludeStartDir);

	bool found = false;

	//A* pathfinding
	while (neighbours.size() > 0 && !found)
	{
		//Find the neighbour closest to end
		int smallestNodeIndex = 0;
		float smallestEstimate = 10000;
		for (int i = 0; i < neighbours.size(); i++)
		{
			float estimate = neighbours[i]->_cost + neighbours[i]->_heuristic;
			if (estimate < smallestEstimate)
			{
				smallestNodeIndex = i;
				smallestEstimate = estimate;
			}
		}
		//Check if it is end, if not add more neighbour
		if (neighbours[smallestNodeIndex]->_mapTile == end)
		{
			found = true;
			MapGraphNode* current = neighbours[smallestNodeIndex];
			while (current->_previousNode != nullptr)
			{
				current->_previousNode->_nextNode = current;
				current = current->_previousNode;
			}
		}
		else
		{
			PathfindingGetNeighbours(neighbours[smallestNodeIndex], end);
		}
		//Remove from neighbour list
		neighbours.erase(neighbours.begin() + smallestNodeIndex);
	}

	//Release memory for unused nodes
	for (MapGraphNode* nNode : neighbours)
	{
		delete nNode;
	}

	if (found)
		return startNode;
	else
		return nullptr;
}

MapGraphNode* TileMap::FindRandomPathToNextIntersection(MapTileObject* start, int excludeStartDir)
{
	MapGraphNode* startNode = new MapGraphNode(start);
	MapGraphNode* current = startNode;
	MapGraphNode* next;
	MapTileObject* tile;
	int previousDir;
	int tileConnections;
	bool doOnce = true;
	do
	{
		if (doOnce)
		{
			previousDir = GetPossibleRandomNextDirection(current->_mapTile->_mapRow, current->_mapTile->_mapCol, excludeStartDir);
			tile = GetTileInDirection(current->_mapTile->_mapRow, current->_mapTile->_mapCol, previousDir);
			doOnce = false;
		}
		else
		{
			if (GetTileInDirection(current->_mapTile->_mapRow, current->_mapTile->_mapCol, previousDir) == nullptr)
			{
				previousDir = GetPossibleRandomNextDirection(current->_mapTile->_mapRow, current->_mapTile->_mapCol, GetOppositeDirection(previousDir));
			}
			tile = GetTileInDirection(current->_mapTile->_mapRow, current->_mapTile->_mapCol, previousDir);
		}
		tileConnections = GetTileNumConnections(tile->_mapRow, tile->_mapCol);
		next = new MapGraphNode(tile);
		current->ConnectNextNode(next);
		current = next;
	} while (tileConnections < 3);
	return startNode;
}

int TileMap::GetTileNumConnections(const int x, const int y) const
{
	if (x >= 0 && x < mapSizeY && y >= 0 && y < mapSizeX)
	{
		int connectionCount = 0;
		for (int dir = 0; dir < 4; dir++)
		{
			MapTileObject* next = GetTileInDirection(x, y, dir);
			if (GetMapTileType(next) > EMapTileType::Wall)
			{
				connectionCount++;
			}
		}
		return connectionCount;
	}
	return -1;
}

int TileMap::GetTileNumConnections(const MapTileObject * tile) const
{
	if (tile != nullptr)
	{
		return GetTileNumConnections(tile->_mapRow, tile->_mapCol);
	}
	return -1;
}

int TileMap::FindNextDirectionInPath(const MapGraphNode* pathNode) const
{
	if (pathNode->_nextNode != nullptr)
	{
		int cRow = pathNode->_mapTile->_mapRow;
		int cCol = pathNode->_mapTile->_mapCol;
		int nRow = pathNode->_nextNode->_mapTile->_mapRow;
		int nCol = pathNode->_nextNode->_mapTile->_mapCol;
		if (cRow != nRow)
		{
			if (cRow < nRow)
				return 0;
			else
				return 2;
		}
		else
		{
			if (cCol < nCol)
				return 1;
			else
				return 3;
		}
	}
	return -1;
}

int TileMap::GetPossibleWithFavourDirection(const int x, const int y, const int priority) const
{
	std::vector<int> possibleReturns;
	for (int dir = 0; dir < 4; dir++)
	{
		MapTileObject* next = GetTileInDirection(x, y, dir);
		if (GetMapTileType(next) > EMapTileType::Wall)
		{
			if (dir == priority)
				return priority;
			possibleReturns.push_back(dir);
		}
	}
	if (possibleReturns.size() > 0)
	{
		return possibleReturns[IRAND_RANGE(0, possibleReturns.size())];
	}
	return -1;
}

void TileMap::CreateMap()
{
	for (int row = 0; row < mapSizeY; row++)
	{
		TileArray temp;
		for (int col = 0; col < mapSizeX; col++)
		{
			temp.push_back(new MapTileObject(row, col, this));
		}
		map.push_back(temp);
	}
}

void TileMap::SetSubRegion(const int startRow, const int startCol, const bool invertVert, const bool invertHori)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (mapUnit[invertVert ? (5 - i) : i][invertHori ? (7 - j) : j])
				map[startRow + i][startCol + j]->SetMapTileType(EMapTileType::Wall);
		}
	}
}

MapTileObject* TileMap::GetTileInDirection(const int row, const int col, const int dir) const
{
	int nextRow = row + static_cast<int>(directions[dir][0]);
	int nextCol = col + static_cast<int>(directions[dir][1]);
	if (nextRow >= 0 && nextRow < mapSizeY && nextCol >= 0 && nextCol < mapSizeX)
	{
		return map[nextRow][nextCol];
	}
	else
	{
		return nullptr;
	}
}

void TileMap::PathfindingGetNeighbours(MapGraphNode* current, MapTileObject* end, int excludeDir)
{
	for (int dir = 0; dir < 4; dir++)
	{
		if (dir == excludeDir)
			continue;

		MapTileObject* nextTile = GetTileInDirection(current->_mapTile->_mapRow, current->_mapTile->_mapCol, dir);

		if (nextTile == nullptr)
			continue;

		//Do not re-create already existing nodes;
		bool existingNode = false;
		for (MapGraphNode* nNode : nodes)
		{
			if (nNode->_mapTile == nextTile)
			{
				existingNode = true;
				break;
			}
		}
		if (existingNode)
			continue;

		if (GetMapTileType(nextTile) >= EMapTileType::Floor)
		{

			MapGraphNode* neighbourNode = new MapGraphNode(nextTile);
			neighbourNode->_cost = current->_cost + current->_weight;
			Vec2 diff = end->_position;
			diff -= current->_mapTile->_position;
			float dist = diff.Length();
			neighbourNode->_heuristic = dist;
			neighbourNode->ConnectPreviousNode(current, true);
			nodes.push_back(neighbourNode);
			neighbours.push_back(neighbourNode);
		}
	}
}

int TileMap::GetOppositeDirection(int dir)
{
	switch (dir)
	{
	case 0:
		return 2;
		break;
	case 1:
		return 3;
		break;
	case 2:
		return 0;
		break;
	case 3:
		return 1;
		break;
	}
	return 0;
}

/*
for (int row = 0; row < mapSizeY; row++)
{
	for (int col = 0; col < mapSizeX; col++)
	{

	}
}
*/

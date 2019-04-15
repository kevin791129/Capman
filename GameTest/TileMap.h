#pragma once
#include "Object\MapTileObject.h"
#include "Utility.h"
#include "Object\ActorObject.h"

typedef std::vector<MapTileObject*> TileArray;
typedef std::vector<TileArray> MapType;

class MapGraphNode
{
public:
	MapTileObject* _mapTile;
	float _cost;
	float _weight;
	float _heuristic;
	MapGraphNode* _previousNode;
	MapGraphNode* _nextNode;
public:
	MapGraphNode(MapTileObject* mapTile) : _mapTile(mapTile), _cost(0), _weight(1), _heuristic(0), _previousNode(nullptr), _nextNode(nullptr) { }
	~MapGraphNode() { }
	void ConnectNextNode(MapGraphNode* next, bool oneWay = false)
	{
		_nextNode = next;
		if (oneWay)
			next->_previousNode = this;
	}
	void ConnectPreviousNode(MapGraphNode* previous, bool oneWay = false)
	{
		_previousNode = previous;
		if (oneWay)
			_previousNode->_nextNode = this;
	}
	MapGraphNode* GetPathStart()
	{
		MapGraphNode* current = this;
		while (current->_previousNode != nullptr)
		{
			current = current->_previousNode;
		}
		return current;
	}
	MapGraphNode* GetPathEnd()
	{
		MapGraphNode* current = this;
		while (current->_nextNode != nullptr)
		{
			current = current->_nextNode;
		}
		return current;
	}
};

typedef std::vector<MapGraphNode*> MapNodeList;

class TileMap
{
private:
	MapType map;
	MapNodeList nodes;
	MapNodeList neighbours;
public:
	//--------------------------------------------------------------------------------------------
	// Constructor and destructor
	//--------------------------------------------------------------------------------------------
	TileMap();
	~TileMap();
	//--------------------------------------------------------------------------------------------
	// Generates new map and return is list of all spawned actors
	//--------------------------------------------------------------------------------------------
	ActorList ResetMap();
	//--------------------------------------------------------------------------------------------
	// Renders the map
	//--------------------------------------------------------------------------------------------
	void Render() const;
	//--------------------------------------------------------------------------------------------
	// Return the tile type give (x, y) in map coord
	//--------------------------------------------------------------------------------------------
	EMapTileType GetMapTileType(const int x, const int y) const;
	EMapTileType GetMapTileType(const MapTileObject* tile) const;
	//--------------------------------------------------------------------------------------------
	// Return int for direction give (x, y) in map coord, 0 = up, 1 = right, 2 = down, 3 = left
	//--------------------------------------------------------------------------------------------
	int GetPossibleRandomNextDirection(const int x, const int y, const int exclude = -1) const;
	MapTileObject* GetTile(const int x, const int y) const;
	//--------------------------------------------------------------------------------------------
	// A* pathfinding, use excludeStartDir to not look in that direction at first, prevent going backwards
	//--------------------------------------------------------------------------------------------
	MapGraphNode* Pathfind(MapTileObject* start, MapTileObject* end, int excludeStartDir = -1);
	//--------------------------------------------------------------------------------------------
	// Finds a random path to next intersection node
	//--------------------------------------------------------------------------------------------
	MapGraphNode* FindRandomPathToNextIntersection(MapTileObject* start, int excludeStartDir = -1);
	//--------------------------------------------------------------------------------------------
	// Return num of connections a tile has
	//--------------------------------------------------------------------------------------------
	int GetTileNumConnections(const int x, const int y) const;
	int GetTileNumConnections(const MapTileObject* tile) const;
	//--------------------------------------------------------------------------------------------
	// Return the direction of next tile if traversing path
	//--------------------------------------------------------------------------------------------
	int FindNextDirectionInPath(const MapGraphNode* pathNode) const;
	int GetPossibleWithFavourDirection(const int x, const int y, const int priority) const;
private:
	void CreateMap();
	void SetSubRegion(const int startRow, const int startCol, const bool invertVert, const bool invertHori);
	//--------------------------------------------------------------------------------------------
	// Return next tile give current tile and direction, 0 = up, 1 = right, 2 = down, 3 = left
	//--------------------------------------------------------------------------------------------
	MapTileObject* GetTileInDirection(const int x, const int y, const int dir) const;
	void PathfindingGetNeighbours(MapGraphNode* current, MapTileObject* end, int excludeDir = -1);
	int GetOppositeDirection(int dir);
};
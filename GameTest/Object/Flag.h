#pragma once
#include "ActorObject.h"
#include "MapTileObject.h"

class Flag : public ActorObject
{
public:
	bool _isHeld;
	ActorObject* _owner;
	//--------------------------------------------------------------------------------------------
	// Flag map row and map col are only accurate if not held, only updates with Drp()
	//--------------------------------------------------------------------------------------------
	int _mapRow;
	int _mapCol;
public:
	//--------------------------------------------------------------------------------------------
	// Constructor and functions from parent class
	//--------------------------------------------------------------------------------------------
	Flag(MapTileObject* tile);
	~Flag() override { }
	void Flag::UpdateObject(float deltaTime) override;
	void Flag::DrawObject() const override;
	void Flag::ResolveCollision(const EActorType otherType, ActorObject* otherActor) override;
	void Pickup(ActorObject* owner);
	void Drop();
};
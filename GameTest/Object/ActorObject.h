#pragma once
#include "BaseObject.h"
#include "..\Utility.h"

class ActorObject : public BaseObject
{
public:
	float _radius;
	EActorType _type;
public:
	//--------------------------------------------------------------------------------------------
	// Constructor and functions from parent class
	//--------------------------------------------------------------------------------------------
	ActorObject() : _radius(0) , _type(EActorType::ENoCollision) { }
	~ActorObject() override { }
	//--------------------------------------------------------------------------------------------
	// Collision check function, all actors have a circle collider (_radius)
	//--------------------------------------------------------------------------------------------
	static bool HasCollision(const ActorObject* actorOne, const ActorObject* actorTwo);
	virtual void ResolveCollision(const EActorType otherType, ActorObject* otherActor) = 0;
};

typedef std::vector<ActorObject*> ActorList;
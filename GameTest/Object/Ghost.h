#pragma once
#include "ActorObject.h"
#include "Movable.h"
#include "Controllable.h"

class Ghost : public ActorObject, public Movable, public Controllable
{
private:
	float _r;
	float _g;
	float _b;
public:
	//--------------------------------------------------------------------------------------------
	// Constructor and functions from parent class
	//--------------------------------------------------------------------------------------------
	Ghost(int x, int y) : _r(1.0f), _g(0.0f), _b(0.0f) { SetPosition((float)y, (float)x); _radius = 0.35f; }
	Ghost(MapTileObject* tile, float r, float g, float b);
	~Ghost() override {  }
	void Ghost::UpdateObject(float deltaTime) override;
	void Ghost::DrawObject() const override;
	void Ghost::ResolveCollision(const EActorType otherType, ActorObject* otherActor) override;
	void Ghost::Move(float deltaTime) override;
};
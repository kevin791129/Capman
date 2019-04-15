#pragma once
#include "ActorObject.h"
#include "Movable.h"
#include "Controllable.h"

class Pacman : public ActorObject, public Movable , public Controllable
{
private:
	float _mouthOpenAngle;
	float _mouthSpeed;
	bool _mouthOpening;
public:
	//--------------------------------------------------------------------------------------------
	// Constructor and functions from parent class
	//--------------------------------------------------------------------------------------------
	Pacman(int x, int y);
	Pacman(MapTileObject* tile);
	~Pacman() override {  }
	void Pacman::UpdateObject(float deltaTime) override;
	void Pacman::DrawObject() const override;
	void Pacman::ResolveCollision(const EActorType otherType, ActorObject* otherActor) override;
	void Pacman::Move(float deltaTime) override;
};
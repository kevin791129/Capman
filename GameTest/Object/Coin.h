#pragma once
#include "ActorObject.h"

class Coin : public ActorObject
{
public:
	//--------------------------------------------------------------------------------------------
	// Constructor and functions from parent class
	//--------------------------------------------------------------------------------------------
	Coin(int x, int y) { SetPosition((float)y, (float)x); _radius = 0.1f; _type = EActorType::ECoins; }
	~Coin() override {  }
	void Coin::UpdateObject(float deltaTime) override;
	void Coin::DrawObject() const override;
	void Coin::ResolveCollision(const EActorType otherType, ActorObject* otherActor) override;
};
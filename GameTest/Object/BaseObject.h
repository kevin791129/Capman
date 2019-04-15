#pragma once
#include "..\stdafx.h"

typedef MathHelper::Vector2<float> Vec2;

class BaseObject
{
public:
	Vec2 _position;
	bool _toBeDestory = false;
public:
	//--------------------------------------------------------------------------------------------
	// Constructor for base object class
	//--------------------------------------------------------------------------------------------
	BaseObject() : _position(Vec2()) { }
	virtual ~BaseObject() { }
	//--------------------------------------------------------------------------------------------
	// Movement functions
	//--------------------------------------------------------------------------------------------
	void SetPosition(const float x, const float y);
	void Translate(const Vec2 moveVector);
	//--------------------------------------------------------------------------------------------
	// Pure virtual functions that needs to be implemented for all child class
	//--------------------------------------------------------------------------------------------
	virtual void UpdateObject(float deltaTime) = 0;
	virtual void DrawObject() const = 0;
};
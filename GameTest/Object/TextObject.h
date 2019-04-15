#pragma once
#include "..\App\app.h"
#include "BaseObject.h"

class TextObject : public BaseObject 
{
private:
	std::string _text;
	float _r;
	float _g;
	float _b;
	void* _font;
public:
	//--------------------------------------------------------------------------------------------
	// Constructor and functions from parent class
	//--------------------------------------------------------------------------------------------
	TextObject() : _text(""), _r(1), _g(1), _b(1), _font(GLUT_BITMAP_TIMES_ROMAN_24) { }
	~TextObject() override { }
	void TextObject::UpdateObject(float deltaTime) override;
	void TextObject::DrawObject() const override;
	//--------------------------------------------------------------------------------------------
	// Set the text displayed related variables
	//--------------------------------------------------------------------------------------------
	void SetString(const std::string text);
	void SetColor(const float r, const float g, const float b);
	void SetFont(void* font);
};
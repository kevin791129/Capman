#include "..\stdafx.h"
#include "TextObject.h"

void TextObject::SetString(const std::string text)
{
	_text = text;
}

void TextObject::SetColor(const float r, const float g, const float b)
{
	_r = r;
	_g = g;
	_b = b;
}

void TextObject::SetFont(void* font)
{
	_font = font;
}

void TextObject::UpdateObject(float deltaTime)
{
	//Stationary object, do nothing
}

void TextObject::DrawObject() const
{
	App::Print(_position._x, _position._y, _text.c_str(), _r, _g, _b, _font);
}

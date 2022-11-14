#include "pch.h"
#include "Object.h"

Object::Object() :
	m_ptPos{},
	m_ptScale{}
{
}

Object::~Object()
{
}


void Object::Render(HDC hdc)
{
	Vector2 position = GetPos();
	Vector2 scale = GetScale();

	Rectangle
	(
		hdc,
		(int)(position.x - scale.x / 2.f),
		(int)(position.y - scale.y / 2.f),
		(int)(position.x + scale.x / 2.f),
		(int)(position.y + scale.y / 2.f)
	);

	SetScale(scale);
}

#include "pch.h"
#include "Vector2.h"

Vector2::Vector2() : x(0.f), y(0.f)
{
}

Vector2::~Vector2()
{
}

Vector2::Vector2(int x, int y) :
	x(float(x)),
	y(float(y))
{
}

Vector2::Vector2(long x, long y) :
	x(float(x)),
	y(float(y))
{
}

Vector2::Vector2(float x, float y) :
	x(x),
	y(y)
{
}

Vector2::Vector2(POINT pt)
	:x((float)pt.x)
	, y((float)pt.y)
{
}

float Vector2::Length()
{
	return sqrt(x * x + y * y);
}

Vector2& Vector2::Normalize()
{
	float fLen = Length();

	assert(fLen != 0);

	x /= fLen;
	y /= fLen;

	return *this;
}
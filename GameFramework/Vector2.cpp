#include "pch.h"
#include "Vector2.h"

Vector2::Vector2()
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
	,y((float)pt.y)
{

}

#pragma once
#include<assert.h>

class Vector2
{
public:
	float x;
	float y;

public:
	Vector2();
	~Vector2();
	Vector2(int x, int y);
	Vector2(long x, long y);
	Vector2(float x, float y);
	Vector2(POINT pt);

	float Length();
	Vector2& Normalize();

	const Vector2& operator+ (const Vector2& v)
	{
		return Vector2(v.x + x, v.y + y);
	}
	const Vector2& operator* (const Vector2& v)
	{
		return Vector2(v.x * x, v.y * y);
	}
	const Vector2& operator/ (const Vector2& v)
	{
		//assert(!(v.x == 0.f || v. == 0.f));
		return Vector2(x / v.x, y / v.y);
	}
	const Vector2& operator- (const Vector2& v)
	{
		return Vector2(x - v.x, y - v.y);
	}
};
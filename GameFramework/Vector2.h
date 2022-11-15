#pragma once
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
};
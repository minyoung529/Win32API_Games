#pragma once
#include "framework.h"

class Hand
{
public:
	Hand();
	Hand(COLORREF color, int thickness, int length, POINT center);
	~Hand();

private:
	COLORREF m_color;	// 바늘 색상
	int m_thickness;	// 바늘 굵기
	int m_length;		// 바늘 길이
	POINT m_center;		// 시계 센터 포지션

public:
	void Render(HDC hdc, float sinX, float cosY);
};


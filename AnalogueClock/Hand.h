#pragma once
#include "framework.h"

class Hand
{
public:
	Hand();
	Hand(COLORREF color, int thickness, int length, POINT center);
	~Hand();

private:
	COLORREF m_color;	// �ٴ� ����
	int m_thickness;	// �ٴ� ����
	int m_length;		// �ٴ� ����
	POINT m_center;		// �ð� ���� ������

public:
	void Render(HDC hdc, float sinX, float cosY);
};


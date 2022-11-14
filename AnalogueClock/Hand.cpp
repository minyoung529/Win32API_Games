#include "Hand.h"
#include "Define.h"

Hand::Hand() : Hand(RGB(0, 0, 0), 1, 10, { SCREEN_WIDTH * 1 / 2, SCREEN_HEIGHT * 1 / 2 })
{}

Hand::Hand(COLORREF color, int thickness, int length, POINT center)
	: m_color(color)
	, m_thickness(thickness)
	, m_length(length)
	, m_center(center)
{}

Hand::~Hand()
{}

void Hand::Render(HDC hdc, float sinX, float cosY)
{
	HPEN hPen = CreatePen(PS_SOLID, m_thickness, m_color);
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

	// startPos�� x y�� ���� ����:	��ħ�� �� �߾��� �ƴ� ������ �ݴ��ʺ��� �����ϱ� ����! (�������� ����)

	POINT startPos = { m_center.x - sinX * 10, m_center.y - cosY * 10 };
	POINT endPos = { m_center.x + sinX * m_length, m_center.y + cosY * m_length };

	MoveToEx(hdc, startPos.x, startPos.y, nullptr);
	LineTo(hdc, endPos.x, endPos.y);

	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
}
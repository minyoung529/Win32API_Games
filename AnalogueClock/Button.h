#pragma once
#include "Clock.h"

class Button
{
protected:
	COLORREF m_color;	// ��ư ����
	POINT m_pos;		// ��ư ���� ������
	POINT m_scale;		// ��ư ������ (����, ����)
	RECT m_rect;		// ��ư ��Ʈ
	bool m_toggle;		// ���

public:
	Button();
	Button(COLORREF color, POINT pos, POINT scale);

	virtual ~Button() {}

public:
	void Init(HWND hWnd);
	void Update(HWND hWnd);
	virtual void Render(HDC hdc);

	// ��ư�� ������ ��
	// �ڽ��� ����
	virtual void OnClickButton() = 0;

private:
	void SetRect();		// Rect �ʱ⼼��
};
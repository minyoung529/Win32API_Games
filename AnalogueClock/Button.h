#pragma once
#include "Clock.h"

class Button
{
protected:
	COLORREF color;
	POINT pos;
	int width;
	int height;
	RECT rect;
	bool toggle;

public:
	Button()
	{
		color = RGB(0, 0, 0);
		memset(&pos, NULL, sizeof(pos));
		width = 20;
		height = 15;
		toggle = false;

		SetRect();
	}

	Button(COLORREF color, POINT pos, int width, int height) :
		color(color), pos(pos), width(width), height(height), toggle(false)
	{
		SetRect();
	}

	virtual ~Button() {}

public:

	void Update(HDC hdc)
	{
		POINT mousePoint;
		GetCursorPos(&mousePoint);

		// 마우스와 충돌 감지
		if (PtInRect(&rect, mousePoint) && (GetAsyncKeyState(VK_LBUTTON) & 0x8001))
		{
			toggle = !toggle;
			OnClickButton();
		}

		Render(hdc);
	}

	void Render(HDC hdc)
	{
		COLORREF buttonColor = (toggle) ? RGB(150, 150, 150) : color;
		HBRUSH hBlueBrush = CreateSolidBrush(buttonColor);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hBlueBrush);

		Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);

		SelectObject(hdc, oldBrush);
		DeleteObject(hBlueBrush);
	}

	// 버튼이 눌렸을 때
	virtual void OnClickButton() = 0;

private:
	// 버튼 Rect 설정
	void SetRect()
	{
		rect.left = pos.x - width;
		rect.right = pos.x + width;
		rect.top = pos.y + height;
		rect.bottom = pos.y - height;
	}
};
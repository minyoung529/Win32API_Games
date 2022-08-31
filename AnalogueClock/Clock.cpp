#include "Clock.h"
#include <math.h>

// 시침 출력
void Clock::RenderHour(SYSTEMTIME time, HDC hdc)
{
	HPEN hPen = CreatePen(PS_SOLID, 16, RGB(255, 0, 0));
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

	// minute을 더한 이유:		시간이 흘러감에 따라
	//							자연스럽게 시침이 변하는 것을 표현하기 위해서

	// ex ) 6시 40분				=> 6 * 30 + 40 / 2 => 180 + 20 => 200 degrees
	float x = sin(PI / 180 * ((double)time.wHour * 30 + time.wMinute / 2));
	float y = -cos(PI / 180 * ((double)time.wHour * 30 + time.wMinute / 2));
	float lenOffset = 0.3f;

	// startPos에 x y를 더한 이유:	시침이 정 중앙이 아닌 방향의 반대쪽부터 시작하기 때문!
	//								(빠져나온 길이)

	POINT startPos = { pos.x - x * radius / 10, pos.y - y * radius / 10 };
	POINT endPos = { pos.x + x * radius * lenOffset, pos.y + y * radius * lenOffset };

	MoveToEx(hdc, startPos.x, startPos.y, nullptr);
	LineTo(hdc, endPos.x, endPos.y);

	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
}

// 초침 출력
void Clock::RenderSecond(SYSTEMTIME time, HDC hdc)
{
	HPEN hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 255));
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

	float x = sin(PI / 180 * time.wSecond * 6);
	float y = -cos(PI / 180 * time.wSecond * 6);
	float lenOffset = 0.7f;

	POINT startPos = { pos.x - x * radius / 10, pos.y - y * radius / 10 };
	POINT endPos = { pos.x + x * radius * lenOffset, pos.y + y * radius * lenOffset };

	MoveToEx(hdc, startPos.x, startPos.y, nullptr);
	LineTo(hdc, endPos.x, endPos.y);

	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
}

// 분침 출력
void Clock::RenderMinute(SYSTEMTIME time, HDC hdc)
{
	HPEN hPen = CreatePen(PS_SOLID, 9, RGB(34, 116, 28));
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

	float x = sin(PI / 180 * (time.wMinute * 6));
	float y = -cos(PI / 180 * (time.wMinute * 6));
	float lenOffset = 0.6f;

	POINT startPos = { pos.x - x * radius / 10, pos.y - y * radius / 10 };
	POINT endPos = { pos.x + x * radius * lenOffset, pos.y + y * radius * lenOffset };

	MoveToEx(hdc, startPos.x, startPos.y, nullptr);
	LineTo(hdc, endPos.x, endPos.y);

	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
}

void Clock::RenderNumber(HDC hdc)
{
	RECT rt;
	float space = 0.95f;

	for (int i = 0; i < 12; i++)
	{
		float x = pos.x + sin(PI / 180 * i * 30) * radius * space;
		float y = pos.y - cos(PI / 180 * i * 30) * radius * space;

		rt.left = x - 4;
		rt.right = x + 4;
		rt.top = y - 4;
		rt.bottom = y + 4;

		HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hBlueBrush);
		FillRect(hdc, &rt, hBlueBrush);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBlueBrush);
	}
}

void Clock::RenderCircle(HDC hdc)
{
	HBRUSH hBlueBrush = CreateSolidBrush(RGB(250, 244, 192));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hBlueBrush);

	float radius = this->radius + 15;
	Ellipse(hdc, pos.x - radius, pos.y + radius, pos.x + radius, pos.y - radius);

	SelectObject(hdc, oldBrush);
	DeleteObject(hBlueBrush);
}

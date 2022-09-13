#include "Clock.h"
#include <math.h>


// 시침 출력
void Clock::RenderHour(SYSTEMTIME time, HDC hdc)
{
	HPEN hPen = CreatePen(PS_SOLID, 16, HOUR_COLOR);
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

	// minute을 더한 이유:		시간이 흘러감에 따라= 자연스럽게 시침이 변하는 것을 표현하기 위해서

	// ex ) 6시 40분				=> 6 * 30 + 40 / 2 => 180 + 20 => 200 degrees
	float x = sin(DEG2RAD * ((double)time.wHour * 30 + time.wMinute / 2));
	float y = -cos(DEG2RAD * ((double)time.wHour * 30 + time.wMinute / 2));

	// startPos에 x y를 더한 이유:	시침이 정 중앙이 아닌 방향의 반대쪽부터 시작하기 때문! (빠져나온 길이)

	POINT endPos = { pos.x + x * radius * HOUR_RATIO, pos.y + y * radius * HOUR_RATIO };

	MoveToEx(hdc, STARTPOSX(pos, x, radius), STARTPOSY(pos, y, radius), nullptr);
	LineTo(hdc, endPos.x, endPos.y);

	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
}

// 초침 출력
void Clock::RenderSecond(SYSTEMTIME time, HDC hdc)
{
	HPEN hPen = CreatePen(PS_SOLID, 5, SECOND_COLOR);
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

	float x = sin(DEG2RAD * time.wSecond * 6);
	float y = -cos(DEG2RAD * time.wSecond * 6);

	POINT endPos = { pos.x + x * radius * SECOND_RATIO, pos.y + y * radius * SECOND_RATIO };

	MoveToEx(hdc, STARTPOSX(pos, x, radius), STARTPOSY(pos, y, radius), nullptr);
	LineTo(hdc, endPos.x, endPos.y);

	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
}

// 분침 출력
void Clock::RenderMinute(SYSTEMTIME time, HDC hdc)
{
	HPEN hPen = CreatePen(PS_SOLID, 9, MINUTE_COLOR);
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

	float x =  sin(DEG2RAD * time.wMinute * 6);
	float y = -cos(DEG2RAD * time.wMinute * 6);

	POINT endPos = { pos.x + x * radius * MINUTE_RATIO, pos.y + y * radius * MINUTE_RATIO };

	MoveToEx(hdc, STARTPOSX(pos, x, radius), STARTPOSY(pos, y, radius), nullptr);
	LineTo(hdc, endPos.x, endPos.y);

	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
}

// 시계 눈금선 출력
void Clock::RenderGraduation(HDC hdc)
{
	float radius = this->radius + 15;

	HPEN hPen = CreatePen(PS_SOLID, 2, GRADUATION_COLOR);
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
	float len = 10;

	for (int i = 0; i < 60; i++)
	{
		float x =  sin(DEG2RAD * i * 6);
		float y = -cos(DEG2RAD * i * 6);

		len = (i % 5 != 0) ? 7 : 16;

		POINT startPos = { pos.x - x * radius,	 pos.y - y * radius };
		POINT endPos = { pos.x - x * (radius - len), pos.y - y * (radius - len) };

		MoveToEx(hdc, startPos.x, startPos.y, nullptr);
		LineTo(hdc, endPos.x, endPos.y);
	}

	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
}

// 시계 숫자 출력
void Clock::RenderNumber(HDC hdc)
{
	RECT rt;
	float space = 0.90f;

	for (int i = 0; i < 12; i++)
	{
		float x = pos.x + sin(DEG2RAD * i * 30) * radius * space;
		float y = pos.y - cos(DEG2RAD * i * 30) * radius * space;

		rt.left = x - 4;
		rt.right = x + 4;
		rt.top = y - 4;
		rt.bottom = y + 4;

		// 중앙 정렬
		SetTextAlign(hdc, TA_CENTER);

		// 숫자 출력
		TCHAR buffer[3];
		wsprintf(buffer, TEXT("%d"), i + 1);
		TextOut(hdc, x, y - 5, buffer, lstrlen(buffer));
	}
}

// 시계 원 출력
void Clock::RenderCircle(HDC hdc)
{
	HBRUSH hBrush = CreateSolidBrush(STROKE_COLOR);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	float radius = this->radius + 15;
	float stroke = 1.05f;
	
	Ellipse(hdc, pos.x - radius * stroke, pos.y + radius * stroke, pos.x + radius * stroke, pos.y - radius * stroke);
	DeleteObject(hBrush);

	hBrush = CreateSolidBrush(CIRCLE_COLOR);
	
	SelectObject(hdc, hBrush);
	Ellipse(hdc, pos.x - radius, pos.y + radius, pos.x + radius, pos.y - radius);

	SelectObject(hdc, oldBrush);
	DeleteObject(hBrush);
}

void Clock::PlaySound(SYSTEMTIME time)
{
	if (clockState & SOUND)
	{
		if (time.wSecond >= 57 && time.wSecond <= 59)
			Beep(500, 200);

		else if (time.wSecond == 0)
			Beep(1000, 400);

		else
			Beep(200, 100);
	}
}

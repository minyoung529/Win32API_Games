#include "Clock.h"
#include "Define.h"
#include "Hand.h"
#include <math.h>

Clock::Clock() : m_radius(0), m_position{}
{}

Clock::Clock(int radius, POINT position)
	: m_radius(radius)
	, m_position(position)
	, m_clockState(HOUR | SECOND | MINUTE | SOUND)
	, m_hourHand(nullptr), m_minuteHand(nullptr), m_secondHand(nullptr)
{}

Clock::~Clock()
{
	delete m_hourHand;
	delete m_minuteHand;
	delete m_secondHand;
}

void Clock::Init()
{
	// �ð�ٴ� ��ü �����
	m_hourHand   = new Hand(HOUR_COLOR, 15, 80, m_position);
	m_minuteHand = new Hand(MINUTE_COLOR, 10, 100, m_position);
	m_secondHand = new Hand(SECOND_COLOR, 5, 125, m_position);
}

void Clock::RenderClock(SYSTEMTIME time, HDC hdc)
{
	RenderCircle(hdc);
	RenderGraduation(hdc);
	RenderNumber(hdc);

	if (m_clockState & SECOND)
		RenderSecond(time, hdc);

	if (m_clockState & MINUTE)
		RenderMinute(time, hdc);

	if (m_clockState & HOUR)
		RenderHour(time, hdc);
}

// ��ħ ���
void Clock::RenderHour(SYSTEMTIME time, HDC hdc)
{
	// minute�� ���� ����:	�ð��� �귯���� ����= �ڿ������� ��ħ�� ���ϴ� ���� ǥ���ϱ� ���ؼ�
	// ex ) 6�� 40��			=> 6 * 30 + 40 / 2 => 180 + 20 => 200 degrees

	float x =  sin(DEG2RAD * ((double)time.wHour * 30 + time.wMinute / 2));
	float y = -cos(DEG2RAD * ((double)time.wHour * 30 + time.wMinute / 2));

	m_hourHand->Render(hdc, x, y);
}

// ��ħ ���
void Clock::RenderMinute(SYSTEMTIME time, HDC hdc)
{
	float x =  sin(DEG2RAD * time.wMinute * 6);
	float y = -cos(DEG2RAD * time.wMinute * 6);

	m_minuteHand->Render(hdc, x, y);
}

// ��ħ ���
void Clock::RenderSecond(SYSTEMTIME time, HDC hdc)
{
	float x =  sin(DEG2RAD * time.wSecond * 6);
	float y = -cos(DEG2RAD * time.wSecond * 6);

	m_secondHand->Render(hdc, x, y);
}

// �ð� ���ݼ� ���
void Clock::RenderGraduation(HDC hdc)
{
	float radius = this->m_radius + 15;

	HPEN hPen = CreatePen(PS_SOLID, 2, GRADUATION_COLOR);
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

	for (int i = 0; i < 60; i++)
	{
		float x = sin(DEG2RAD * i * 6);
		float y = -cos(DEG2RAD * i * 6);

		// 5�и��� �� �� ����
		float len = (i % 5 == 0) ? 15 : 7;

		POINT startPos = { m_position.x + x * radius,	 m_position.y + y * radius };
		POINT endPos = { startPos.x - x * len, startPos.y - y * len};

		MoveToEx(hdc, startPos.x, startPos.y, nullptr);
		LineTo(hdc, endPos.x, endPos.y);
	}

	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
}

// �ð� ���� ���
void Clock::RenderNumber(HDC hdc)
{
	RECT rt;
	float space = 0.90f;

	for (int i = 0; i < 12; i++)
	{
		float x = m_position.x + sin(DEG2RAD * i * 30) * m_radius * space;
		float y = m_position.y - cos(DEG2RAD * i * 30) * m_radius * space;

		rt.left = x - 4;
		rt.right = x + 4;
		rt.top = y - 4;
		rt.bottom = y + 4;

		// �߾� ����
		SetTextAlign(hdc, TA_CENTER);

		// ���� ���
		TCHAR buffer[3];
		int time = (i == 0) ? 12 : i;
		wsprintf(buffer, TEXT("%d"), time);
		TextOut(hdc, x, y - 5, buffer, lstrlen(buffer));
	}
}

// �ð� �� ���
void Clock::RenderCircle(HDC hdc)
{
	HBRUSH hBrush = CreateSolidBrush(STROKE_COLOR);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	// �����ְ�
	int radius = m_radius + 15;
	int stroke = 7;

	Ellipse(hdc, m_position.x - radius - stroke, m_position.y + radius + stroke, m_position.x + radius + stroke, m_position.y - radius - stroke);
	DeleteObject(hBrush);

	hBrush = CreateSolidBrush(CIRCLE_COLOR);

	SelectObject(hdc, hBrush);
	Ellipse(hdc, m_position.x - radius, m_position.y + radius, m_position.x + radius, m_position.y - radius);

	SelectObject(hdc, oldBrush);
	DeleteObject(hBrush);
}

// �߻߻� ��--
void Clock::PlaySound(SYSTEMTIME time)
{
	if (m_clockState & SOUND)
	{
		if (time.wSecond >= 57 && time.wSecond <= 59)
			Beep(500, 400);

		else if (time.wSecond == 0)
			Beep(1000, 1000);
	}
}
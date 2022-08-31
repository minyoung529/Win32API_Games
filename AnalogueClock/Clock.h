#pragma once
#include "framework.h"

#define	HOUR	1
#define	MINUTE	2
#define	SECOND	4
#define	SOUND	8

class Clock
{
private:
	int radius;
	POINT pos;
	int clockState = HOUR | MINUTE | SECOND;

public:
	Clock() : radius(0)
	{
		memset(&pos, 0, sizeof(pos));
	}

	Clock(int radius, POINT scale) : radius(radius)
	{
		pos.x = scale.x * 0.5f;
		pos.y = scale.y * 0.5f;
	}

	Clock(int radius, POINT scale, int clockState) : Clock(radius, scale)
	{
		this->clockState = clockState;
	}

	virtual ~Clock() {}

	void RenderClock(SYSTEMTIME time, HDC hdc)
	{
		RenderCircle(hdc);
		RenderGraduation(hdc);

		if (clockState & SECOND)
			RenderSecond(time, hdc);

		if (clockState & MINUTE)
			RenderMinute(time, hdc);

		if (clockState & HOUR)
			RenderHour(time, hdc);

		if (clockState & SOUND)
		{
			if (time.wSecond >= 57 && time.wSecond <= 59)
				Beep(500, 200);
			else if (time.wSecond == 0)
				Beep(1000, 400);
		}

		RenderNumber(hdc);
	}

	void RenderHour(SYSTEMTIME systemTime, HDC hdc);
	void RenderSecond(SYSTEMTIME systemTime, HDC hdc);
	void RenderMinute(SYSTEMTIME systemTime, HDC hdc);

	void RenderGraduation(HDC hdc);
	void RenderNumber(HDC hdc);
	void RenderCircle(HDC hdc);

public:
	void AddClockState(int state)
	{
		clockState |= state;
	}

	void RemoveClockState(int state)
	{
		clockState ^= state;
	}
};
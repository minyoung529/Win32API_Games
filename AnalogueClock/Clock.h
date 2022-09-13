#pragma once
#include "framework.h"

// 상태 온오프 플래그
#define	HOUR			1
#define	MINUTE			2
#define	SECOND			4
#define	SOUND			8

// 반지름에 따른 시곗바늘 비율
#define HOUR_RATIO		0.3f
#define MINUTE_RATIO	0.6f
#define SECOND_RATIO	0.7f


#define	STARTPOSX(pos, x, radius)	(pos.x - (((x) * radius) / 10))
#define	STARTPOSY(pos, x, radius)	(pos.y - (((y) * radius) / 10))

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

public:
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

		RenderNumber(hdc);
	}

	void PlaySound(SYSTEMTIME time);

	void AddClockState(int state)
	{
		clockState |= state;
	}

	void RemoveClockState(int state)
	{
		clockState ^= state;
	}

private:
	void RenderHour(SYSTEMTIME systemTime, HDC hdc);
	void RenderSecond(SYSTEMTIME systemTime, HDC hdc);
	void RenderMinute(SYSTEMTIME systemTime, HDC hdc);

	void RenderGraduation(HDC hdc);
	void RenderNumber(HDC hdc);
	void RenderCircle(HDC hdc);
};
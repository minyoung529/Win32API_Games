#pragma once
#include "framework.h"
#include "Define.h"

class Hand;

class Clock
{
private:
	int m_radius;			// 시계의 반지름
	POINT m_position;		// 현재 센터 위치
	int m_clockState = HOUR | MINUTE | SECOND | SOUND;	// 비트마스크 (현 상태: 시침, 분침, 초침, 사운드 모든 걸 표현)

	Hand* m_hourHand;		// 시침 객체
	Hand* m_minuteHand;		// 분침 객체
	Hand* m_secondHand;		// 초침 객체

public:
	Clock();
	Clock(int radius, POINT position);
	~Clock();

public:
	void Init();
	void RenderClock(SYSTEMTIME time, HDC hdc);			// 시계 출력
	void PlaySound(SYSTEMTIME time);					// 사운드

	void AddClockState(int state)						// 시계 상태 더하기
	{
		m_clockState |= state;
	}

	void RemoveClockState(int state)					// 시계 상태 빼기
	{
		m_clockState ^= state;
	}

private:
	void RenderHour(SYSTEMTIME systemTime, HDC hdc);	// 시침 출력
	void RenderMinute(SYSTEMTIME systemTime, HDC hdc);	// 분침 출력
	void RenderSecond(SYSTEMTIME systemTime, HDC hdc);	// 초침 출력

	void RenderGraduation(HDC hdc);						// 눈금 출력
	void RenderNumber(HDC hdc);							// 숫자 출력
	void RenderCircle(HDC hdc);							// 시계 원 출력
};
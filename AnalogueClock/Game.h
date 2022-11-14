#pragma once
#include "Clock.h"
#include "ClockToggle.h"

class ToggleManager;

class Game
{
public:
	Game();
	~Game();

private:
	HWND m_hWnd;					// 윈도우 핸들
	SYSTEMTIME m_systemTime;		// 가져올 시스템 시간
	int m_radius;					// 시계 반지름

private:
	
	Clock* m_clock;					// 시계 객체
	ToggleManager* m_toggleManager;	// 버튼 관리자

public:
	void Init(HWND hWnd);
	void Update();
	void Render(HDC hdc);
	void Release();
	void UpdatePerSec();			// 1초에 한번씩 호출
};
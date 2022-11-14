#pragma once
#include "framework.h"

class ClockToggle;
class Clock;

class ToggleManager
{
public:
	void Init(Clock* clock);
	void Update(HWND hWnd);
	void Render(HDC hdc);
	void Release();

private:
	// 토글 버튼 UI
	ClockToggle* m_hourToggle;
	ClockToggle* m_minuteToggle;
	ClockToggle* m_secondToggle;
	ClockToggle* m_soundToggle;
};
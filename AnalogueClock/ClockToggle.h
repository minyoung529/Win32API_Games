#pragma once
#include "Button.h"
#include "Clock.h"
#include "framework.h"

class ClockToggle : public Button
{
private:
	Clock* m_clock;
	int m_onOffState;
	TCHAR m_name[10];

public:
	ClockToggle();
	ClockToggle(COLORREF color, POINT pos, POINT scale, Clock* clock, int onOffState, const wchar_t* buttonName);
	~ClockToggle() {}

public:
	void OnClickButton() override;
	virtual	void Render(HDC hdc) override;
};
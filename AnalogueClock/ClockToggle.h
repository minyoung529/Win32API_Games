#pragma once
#include "Button.h"
#include "Clock.h"

class ClockToggle : public Button
{
private:
	Clock* clock;
	int onOffState;
	TCHAR name[10];

public:
	ClockToggle() : Button()
	{
		clock = NULL;
		onOffState = 0;
	}

	ClockToggle(COLORREF color, POINT pos, int width, int height, Clock* clock, int onOffState, const wchar_t* buttonName)
		: Button(color, pos, width, height)
		, clock(clock)
		, onOffState(onOffState)
	{
		wsprintf(name, buttonName);
	}

	~ClockToggle() {}

public:
	void OnClickButton() override
	{
		if (toggle)
		{
			clock->RemoveClockState(onOffState);
		}
		else
		{
			clock->AddClockState(onOffState);
		}
	}

	void Render(HDC hdc)
	{
		Button::Render(hdc);

		// Áß¾Ó Á¤·Ä
		SetTextAlign(hdc, TA_CENTER);

		TextOut(hdc, rect.left + width, rect.top + height / 2, name, lstrlen(name));
	}
};
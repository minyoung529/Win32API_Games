#pragma once
#include "Button.h"
#include "Clock.h"

class ClockToggle : public Button
{
private:
	Clock* clock;
	int onOffState;

public:
	ClockToggle() : Button()
	{
		clock = NULL;
		onOffState = 0;
	}

	ClockToggle(COLORREF color, POINT pos, int width, int height, Clock* clock, int onOffState)
		: Button(color, pos, width, height)
		, clock(clock)
		, onOffState(onOffState) 
	{}

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
};
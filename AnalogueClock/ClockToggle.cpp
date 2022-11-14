#pragma once
#include "ClockToggle.h"

ClockToggle::ClockToggle() : Button()
{
	m_clock = NULL;
	m_onOffState = 0;
}

ClockToggle::ClockToggle(COLORREF color, POINT pos, POINT scale, Clock* clock, int onOffState, const wchar_t* buttonName)
	: Button(color, pos, scale)
	, m_clock(clock)
	, m_onOffState(onOffState)
{
	wsprintf(m_name, buttonName);
}

void ClockToggle::OnClickButton()
{
	if (m_toggle)
	{
		// �ð迡�� ������ �ִ� ���¸� ����
		m_clock->RemoveClockState(m_onOffState);
	}
	else
	{
		// �ð迡�� ������ �ִ� ���¸� �ٽ� ���Ѵ�
		m_clock->AddClockState(m_onOffState);
	}
}

void ClockToggle::Render(HDC hdc)
{
	Button::Render(hdc);

	// �߾� ����
	SetTextAlign(hdc, TA_CENTER);
	TextOut(hdc, m_rect.left + m_scale.x / 2, m_rect.top + m_scale.y / 4, m_name, lstrlen(m_name));
}
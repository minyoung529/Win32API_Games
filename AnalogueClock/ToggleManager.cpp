#include "ToggleManager.h"
#include "ClockToggle.h"
#include "Define.h"

void ToggleManager::Init(Clock* clock)
{
	// �ð� ��۵� ����
	m_hourToggle = new ClockToggle(HOUR_COLOR, { 40,450 }, { 60, 40 }, clock, HOUR, L"��ħ");
	m_minuteToggle = new ClockToggle(MINUTE_COLOR, { 140,450 }, { 60, 40 }, clock, MINUTE, L"��ħ");
	m_secondToggle = new ClockToggle(SECOND_COLOR, { 240,450 }, { 60, 40 }, clock, SECOND, L"��ħ");
	m_soundToggle = new ClockToggle(SOUND_COLOR, { 340,450 }, { 60, 40 }, clock, SOUND, L"�Ҹ�");
}

void ToggleManager::Update(HWND hWnd)
{
	m_hourToggle->Update(hWnd);
	m_minuteToggle->Update(hWnd);
	m_secondToggle->Update(hWnd);
	m_soundToggle->Update(hWnd);
}

void ToggleManager::Render(HDC hdc)
{
	m_hourToggle->Render(hdc);
	m_minuteToggle->Render(hdc);
	m_secondToggle->Render(hdc);
	m_soundToggle->Render(hdc);
}

void ToggleManager::Release()
{
	delete m_hourToggle;
	delete m_minuteToggle;
	delete m_secondToggle;
	delete m_soundToggle;
}
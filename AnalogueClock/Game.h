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
	HWND m_hWnd;					// ������ �ڵ�
	SYSTEMTIME m_systemTime;		// ������ �ý��� �ð�
	int m_radius;					// �ð� ������

private:
	
	Clock* m_clock;					// �ð� ��ü
	ToggleManager* m_toggleManager;	// ��ư ������

public:
	void Init(HWND hWnd);
	void Update();
	void Render(HDC hdc);
	void Release();
	void UpdatePerSec();			// 1�ʿ� �ѹ��� ȣ��
};
#pragma once
#include "framework.h"
#include "Define.h"

class Hand;

class Clock
{
private:
	int m_radius;			// �ð��� ������
	POINT m_position;		// ���� ���� ��ġ
	int m_clockState = HOUR | MINUTE | SECOND | SOUND;	// ��Ʈ����ũ (�� ����: ��ħ, ��ħ, ��ħ, ���� ��� �� ǥ��)

	Hand* m_hourHand;		// ��ħ ��ü
	Hand* m_minuteHand;		// ��ħ ��ü
	Hand* m_secondHand;		// ��ħ ��ü

public:
	Clock();
	Clock(int radius, POINT position);
	~Clock();

public:
	void Init();
	void RenderClock(SYSTEMTIME time, HDC hdc);			// �ð� ���
	void PlaySound(SYSTEMTIME time);					// ����

	void AddClockState(int state)						// �ð� ���� ���ϱ�
	{
		m_clockState |= state;
	}

	void RemoveClockState(int state)					// �ð� ���� ����
	{
		m_clockState ^= state;
	}

private:
	void RenderHour(SYSTEMTIME systemTime, HDC hdc);	// ��ħ ���
	void RenderMinute(SYSTEMTIME systemTime, HDC hdc);	// ��ħ ���
	void RenderSecond(SYSTEMTIME systemTime, HDC hdc);	// ��ħ ���

	void RenderGraduation(HDC hdc);						// ���� ���
	void RenderNumber(HDC hdc);							// ���� ���
	void RenderCircle(HDC hdc);							// �ð� �� ���
};
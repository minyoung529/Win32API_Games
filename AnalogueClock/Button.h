#pragma once
#include "Clock.h"

class Button
{
protected:
	COLORREF m_color;	// 버튼 색상
	POINT m_pos;		// 버튼 센터 포지션
	POINT m_scale;		// 버튼 스케일 (가로, 세로)
	RECT m_rect;		// 버튼 렉트
	bool m_toggle;		// 토글

public:
	Button();
	Button(COLORREF color, POINT pos, POINT scale);

	virtual ~Button() {}

public:
	void Init(HWND hWnd);
	void Update(HWND hWnd);
	virtual void Render(HDC hdc);

	// 버튼이 눌렸을 때
	// 자식이 정의
	virtual void OnClickButton() = 0;

private:
	void SetRect();		// Rect 초기세팅
};
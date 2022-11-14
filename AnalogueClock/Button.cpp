#include "Button.h"

Button::Button() : Button(RGB(0, 0, 0), {}, { 20,15 })
{
}

Button::Button(COLORREF color, POINT pos, POINT scale) :
	m_color(color), m_pos(pos), m_scale(scale), m_toggle(false)
{
	SetRect();
}

void Button::Init(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	Render(hdc);
	ReleaseDC(hWnd, hdc);
}

void Button::Update(HWND hWnd)
{
	POINT mousePoint;
	GetCursorPos(&mousePoint);
	ScreenToClient(hWnd, &mousePoint);

	// ���콺�� �浹 ����
	if (PtInRect(&m_rect, mousePoint))
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 1)
		{
			// �浹�ϸ� ����� �ݴ��, OnClickButton�� ȣ���Ѵ�
			m_toggle = !m_toggle;
			OnClickButton();
		}
	}
}

void Button::Render(HDC hdc)
{
	// ���� ���۸�
	HDC memDC = CreateCompatibleDC(hdc);
	HBITMAP bitmap = CreateCompatibleBitmap(hdc, SCREEN_WIDTH, SCREEN_HEIGHT);
	SelectObject(memDC, bitmap);

	COLORREF buttonColor = (m_toggle) ? RGB(150, 150, 150) : m_color;
	HBRUSH hBlueBrush = CreateSolidBrush(buttonColor);
	HBRUSH oldBrush = (HBRUSH)SelectObject(memDC, hBlueBrush);

	Rectangle(memDC, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);
	BitBlt(hdc, m_rect.left, m_rect.top, m_scale.x, m_scale.y, memDC, m_rect.left, m_rect.top, SRCCOPY);

	DeleteObject(hBlueBrush);
	DeleteDC(memDC);
}

void Button::SetRect()
{
	m_rect.left		= m_pos.x - m_scale.x / 2;
	m_rect.right	= m_pos.x + m_scale.x / 2;
	m_rect.top		= m_pos.y - m_scale.y / 2;
	m_rect.bottom	= m_pos.y + m_scale.y / 2;
}
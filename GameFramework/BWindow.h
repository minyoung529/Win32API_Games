#pragma once

class BWindow
{
public:
	BWindow();
	~BWindow();

public:
	ATOM                MyRegisterClass();
	static LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
	int					Run(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow);
	void				WindowCreate();
	void				WindowShow(int nCmdShow);
	void				WindowUpdate();
	int					MessageLoop();

private:
	HWND				m_hWnd;
	HINSTANCE			m_hInstnace;

public:
	const HWND&			GetHwndHandle() { return m_hWnd; }
	const HINSTANCE&	etHInstanceHandle() { return m_hInstnace; }
};
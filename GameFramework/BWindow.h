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

protected:
	HWND				m_hWnd;
	HINSTANCE			m_hInstnace;
};
#ifndef	  BWINDOW_H
#define	  BWINDOW_H

#include "BBasisStd.h"

class BWindow
{
public:
	BWindow();
	~BWindow();

public:
	int						Run(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	void					registerWndClass();
	void					createWindow();
	void					showWindow(int nCmdShow);
	int						messageLoop();

public:
	virtual void			Startup() = 0;
	virtual void			MainLoop() = 0;
	virtual void			Cleanup() = 0;

protected:
	HWND					m_hWnd;
	HINSTANCE				m_hInstance;

public:
	HWND					GetWndHandle();
	HINSTANCE				GetInstanceHandle();

};
#endif // BWINDOW_H
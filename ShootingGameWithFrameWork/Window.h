#ifndef WINDOW_H
#define WINDOW_H

#include"BasisStd.h"

class Window
{
public :
	Window();
	~Window();

public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
	// Wnd Ω√¿€¡°
	int Run(HINSTANCE hInst, LPWSTR plCmdLine, int nCmdShow);
	int MessageLoop();

private:
	void RegisterWndClass();
	void CreateWnd();
	void ShowWnd(int nCmdShow);

public:
	virtual void StartUp() = 0;
	virtual void MainLoop() = 0;
	virtual void Cleanup() = 0;

protected:
	HWND hWnd;
	HINSTANCE hInst;

public:
	HWND GetWndHandle();
	HINSTANCE GetInstanceHandle();
};

#endif
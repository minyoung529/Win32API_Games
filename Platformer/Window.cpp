#include "Window.h"

Window::Window()
{
}

Window::~Window()
{
}

LRESULT Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

int Window::Run(HINSTANCE hInst, LPWSTR plCmdLine, int nCmdShow)
{
	this->hInst = hInst;

	RegisterWndClass();
	CreateWnd();
	ShowWnd(nCmdShow);
	MessageLoop();

	return 0;
}

int Window::MessageLoop()
{
	MSG msg;
	// 구조체 초기화할 때 많이 쓰인다.
	memset(&msg, 0, sizeof(msg));

	StartUp();

	//게임 메인 루프
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			MainLoop();
		}
	}

	Cleanup();
	return (int)msg.wParam;
}

void Window::RegisterWndClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = Window::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInst;
	wcex.hIcon = LoadIcon(hInst, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = TEXT("GameFramework");
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	RegisterClassExW(&wcex);
}

void Window::CreateWnd()
{
	hWnd = CreateWindowW(TEXT("GameFramework"), TEXT("GameFramework!"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInst, nullptr);
}

void Window::ShowWnd(int nCmdShow)
{
	ShowWindow(hWnd, nCmdShow);
}

HWND Window::GetWndHandle()
{
	return hWnd;
}

HINSTANCE Window::GetInstanceHandle()
{
	return hInst;
}

#include "BWindow.h"

BWindow::BWindow() : m_hWnd(NULL), m_hInstance(NULL)
{
}

BWindow::~BWindow()
{
}

int BWindow::Run(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	m_hInstance = hInstance;

	this->registerWndClass();
	this->createWindow();
	this->showWindow(nCmdShow);

	return this->messageLoop();
}

LRESULT CALLBACK BWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void BWindow::registerWndClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = BWindow::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInstance;
	wcex.hIcon = LoadIcon(m_hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = BASIS_WINDOW_NAME;
	wcex.hIconSm = LoadIcon(m_hInstance, IDI_APPLICATION);

	RegisterClassExW(&wcex);
}

void BWindow::createWindow()
{
	m_hWnd = CreateWindowW(BASIS_WINDOW_NAME, TEXT("FrameWork"), WS_OVERLAPPEDWINDOW,
		 	 CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
		     nullptr, nullptr, m_hInstance, nullptr);
}

void BWindow::showWindow(int nCmdShow)
{
	ShowWindow(m_hWnd, nCmdShow);
}

int BWindow::messageLoop()
{
	MSG msg;
	memset(&msg, 0, sizeof(msg));

	this->Startup();

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			this->MainLoop();	
		}
	}

	this->Cleanup();

	return (int)msg.wParam;
}

HWND BWindow::GetWndHandle()
{
	return m_hWnd;
}

HINSTANCE BWindow::GetInstanceHandle()
{
	return m_hInstance;
}

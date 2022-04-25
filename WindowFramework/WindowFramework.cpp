#include "framework.h"
#include "WindowFramework.h"

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib");

#define MAX_LOADSTRING 100

HINSTANCE g_hInst;                                // 현재 인스턴스입니다.
HWND g_hWnd;                                    // 생성된 윈도우의 핸들

WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
SYSTEMTIME sys;

void Init();
void Release();
void Render();
void Update();

POINT rectPosition;
POINT mousePosition;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WINDOWFRAMEWORK, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWFRAMEWORK));

	MSG msg;

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Update();
			Render();
		}
	}

	return (int)msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWFRAMEWORK));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = /*MAKEINTRESOURCEW(IDC_WINDOWFRAMEWORK)*/nullptr;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	g_hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	HWND hWnd = CreateWindowW(szWindowClass, TEXT("Framework!"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
		return FALSE;

	g_hWnd = hWnd;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void Init()
{
}

void Release()
{
}

void Render()
{
	HDC hdc = GetDC(g_hWnd);
	HDC hMemDC = CreateCompatibleDC(hdc);
	RECT rt;
	GetClientRect(g_hWnd, &rt);

	HBITMAP hBitmap = CreateCompatibleBitmap(hMemDC, rt.right, rt.bottom);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);

	FillRect(hMemDC, &rt, (HBRUSH)COLOR_BACKGROUND);
	Rectangle(hMemDC, rectPosition.x, rectPosition.y, rectPosition.x + 100, rectPosition.y + 100);

	//윈도우 기준
	TCHAR str[128];
	wsprintf(str, TEXT("[윈도우 기준 x: %4d, y: %4d]"), mousePosition.x, mousePosition.y);
	TextOut(hMemDC, 10, 10, str, lstrlen(str));

	ScreenToClient(g_hWnd, &mousePosition);
	wsprintf(str, TEXT("[클라이언트 기준 x: %4d, y: %4d]"), mousePosition.x, mousePosition.y);
	TextOut(hMemDC, 10, 30, str, lstrlen(str));

	BitBlt(hdc, 0, 0, rt.right, rt.bottom, hMemDC, 0, 0, SRCCOPY);

	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hBitmap);
	DeleteDC(hMemDC);
	ReleaseDC(g_hWnd, hdc);
}

void Update()
{
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		rectPosition.y--;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		rectPosition.y++;
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		rectPosition.x--;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		rectPosition.x++;
	}

	GetCursorPos(&mousePosition);

	if (GetAsyncKeyState(VK_LBUTTON) & 0x0001)
	{
		PlaySound(TEXT("Laugh.wav"), nullptr, SND_FILENAME | SND_ASYNC);
	}
}

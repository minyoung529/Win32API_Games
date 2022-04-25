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
	Init();

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

HBITMAP bitmap;
POINT imageSize;

void Init()
{
	bitmap = (HBITMAP)LoadImage(g_hInst, TEXT("dd.bmp"), IMAGE_BITMAP, 0,0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	BITMAP bit;
	GetObject(bitmap, sizeof(BITMAP), &bit);
	imageSize.x = bit.bmWidth;
	imageSize.y = bit.bmHeight;
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
	//Rectangle(hMemDC, rectPosition.x, rectPosition.y, rectPosition.x + 100, rectPosition.y + 100);

	////윈도우 기준
	//TCHAR str[128];
	//wsprintf(str, TEXT("[윈도우 기준 x: %4d, y: %4d]"), mousePosition.x, mousePosition.y);
	//TextOut(hMemDC, 10, 10, str, lstrlen(str));

	//ScreenToClient(g_hWnd, &mousePosition);
	//wsprintf(str, TEXT("[클라이언트 기준 x: %4d, y: %4d]"), mousePosition.x, mousePosition.y);
	//TextOut(hMemDC, 10, 30, str, lstrlen(str));

	HDC hBitmapDC = CreateCompatibleDC(hMemDC);
	HBITMAP oldImage = (HBITMAP)SelectObject(hBitmapDC, bitmap);
	BitBlt(hMemDC, 50, 50, imageSize.x, imageSize.y, hBitmapDC, 0, 0, SRCCOPY);
	SelectObject(hBitmapDC, oldImage);

	BitBlt(hdc, 0, 0, rt.right, rt.bottom, hMemDC, 0, 0, SRCCOPY);

	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hBitmap);
	DeleteDC(hMemDC);
	DeleteDC(hBitmapDC);
	ReleaseDC(g_hWnd, hdc);
}

void Update()
{
	/*
	static float fStartTime = (float)timeGetTime() * 0.001f;
	static TCHAR szTemp[256];
	static DWORD dwCount = 0;

	float fNowTime = (float)timeGetTime() * 0.001f;

	if (fNowTime - fStartTime >= 1.0f)
	{
		dwCount++;
		wsprintf(szTemp, TEXT("1초마다 호출 : %d"), dwCount);

		SetWindowTextW(g_hWnd, szTemp);
		fStartTime = fNowTime;
	}*/

	/*static DWORD dwStartTick = GetTickCount();
	static TCHAR szTemp[256];
	static DWORD dwCount = 0;

	if (GetTickCount64() - dwStartTick >= 1000/60)
	{
		dwCount++;
		wsprintf(szTemp, TEXT("1초마다 호출 : %d"), dwCount);
		SetWindowTextW(g_hWnd, szTemp);

		dwStartTick = GetTickCount64();
	}*/
}
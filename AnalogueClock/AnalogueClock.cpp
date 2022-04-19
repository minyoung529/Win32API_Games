// AnalogueClock.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "AnalogueClock.h"
#include <math.h>

#define MAX_LOADSTRING 100
#define PI 3.141592
SYSTEMTIME st;
//화면의 반지름
int radius;
int nWidth;
int nHeight;

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_ANALOGUECLOCK, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 애플리케이션 초기화를 수행합니다:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ANALOGUECLOCK));

	MSG msg;

	// 기본 메시지 루프입니다:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ANALOGUECLOCK));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_ANALOGUECLOCK);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		0, 0, 400, 400, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		RECT rt;
		GetClientRect(hWnd, &rt);
		nWidth = rt.right - rt.left;
		nHeight = rt.bottom - rt.top;
		radius = (nWidth > nHeight) ? nHeight * 9 / 20 : nWidth * 9 / 20;

		SetTimer(hWnd, 1, 1000, nullptr);
	}break;
	case WM_TIMER:
	{
		InvalidateRect(hWnd, nullptr, true);
	}break;
	case WM_CHAR:
	{
		if (wParam == 27)
		{
			DestroyWindow(hWnd);
		}
	}break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		float x, y;
		RECT rt;

		for (int i = 0; i < 12; i++)
		{
			x = nWidth / 2 + sin(2 * PI / 12 * i) * radius;
			y = nHeight / 2 - cos(2 * PI / 12 * i) * radius;
			rt.left = x - 4;
			rt.right = x + 4;
			rt.top = y - 4;
			rt.bottom = y + 4;

			HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));
			HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hBlueBrush);
			FillRect(hdc, &rt, hBlueBrush);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBlueBrush);
		}

		GetLocalTime(&st);
		// 시침
		HPEN hPen = CreatePen(PS_SOLID, 16, RGB(255, 0, 0));
		HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

		// minute을 더한 이유는 시간이 흘러감에 따라
		// 자연스럽게 시침이 변하는 것을 표현하기 위해서
		x = sin(2 * PI * (st.wHour * 60 + st.wMinute) / 720);
		y = -cos(2 * PI * (st.wHour * 60 + st.wMinute) / 720);

		MoveToEx(hdc, nWidth / 2 + x * radius / 2, nHeight / 2 + y * radius / 2, nullptr);
		LineTo(hdc, nWidth / 2 - x * radius / 10, nHeight / 2 - y * radius / 10);

		SelectObject(hdc, hOldPen);
		DeleteObject(hPen);

		//분침
		hPen = CreatePen(PS_SOLID, 9, RGB(0, 255, 0));
		hOldPen = (HPEN)SelectObject(hdc, hPen);

		x = sin(2 * PI * st.wMinute / 60);
		y = -cos(2 * PI * st.wMinute / 60);

		MoveToEx(hdc, nWidth / 2 + x * radius * 2 / 3, nHeight / 2 + y * radius * 2 / 3, nullptr);
		LineTo(hdc, nWidth / 2 - x * radius / 10, nHeight / 2 - y * radius / 10);

		SelectObject(hdc, hOldPen);
		DeleteObject(hPen);

		//초침
		hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 255));
		hOldPen = (HPEN)SelectObject(hdc, hPen);

		x = sin(2 * PI * st.wSecond / 60);
		y = -cos(2 * PI * st.wSecond / 60);

		MoveToEx(hdc, nWidth / 2 + x * radius * 4 / 5, nHeight / 2 + y * radius * 4 / 5, nullptr);
		LineTo(hdc, nWidth / 2 - x * radius / 10, nHeight / 2 - y * radius / 10);

		SelectObject(hdc, hOldPen);
		DeleteObject(hPen);

		if (st.wSecond >= 57 && st.wSecond <= 59)
			Beep(500, 200);
		else if (st.wSecond == 0)
			Beep(1000, 400);

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
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

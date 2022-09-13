#include "framework.h"
#include "AnalogueClock.h"
#include "Clock.h"
#include "ClockToggle.h"
#include <math.h>

// 가져올 시스템 시간
SYSTEMTIME systemTime;

//화면의 반지름
int radius;
int nWidth;
int nHeight;

// 시계 객체
Clock* clock;

// 토글 UI
ClockToggle* hourToggle;
ClockToggle* minuteToggle;
ClockToggle* secondToggle;
ClockToggle* soundToggle;

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// Main 함수
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

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

// 창 등록
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
		0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, nullptr, nullptr, hInstance, nullptr);

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
		radius = (nWidth > nHeight) ? nHeight * 8 / 20 : nWidth * 8 / 20;

		// 시계 생성
		clock = new Clock(radius, { nWidth, nWidth }, HOUR | SECOND | MINUTE | SOUND);

		// 시계 토글들 생성
		hourToggle =	new ClockToggle(HOUR_COLOR, { 40,450 }, 30, 20, clock, HOUR, L"시침");
		minuteToggle =	new ClockToggle(MINUTE_COLOR, { 140,450 }, 30, 20, clock, MINUTE, L"분침");
		secondToggle =	new ClockToggle(SECOND_COLOR, { 240,450 }, 30, 20, clock, SECOND, L"초침");
		soundToggle =	new ClockToggle(SOUND_COLOR, { 340,450 }, 30, 20, clock, SOUND, L"소리");

		SetTimer(hWnd, SECOND_TIMER, 1000, nullptr);
		SetTimer(hWnd, RENDER_TIMER, 100, nullptr);
	}break;
	case WM_TIMER:
	{
		switch (wParam)
		{
		case SECOND_TIMER:
			clock->PlaySound(systemTime);
			break;

		case RENDER_TIMER:
			InvalidateRect(hWnd, nullptr, true);
			break;

		default:
			clock->PlaySound(systemTime);
			InvalidateRect(hWnd, nullptr, true);
		}
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

		GetLocalTime(&systemTime);

		// 토글 버튼들 
		hourToggle	->Update(hdc, hWnd);
		minuteToggle->Update(hdc, hWnd);
		secondToggle->Update(hdc, hWnd);
		soundToggle	->Update(hdc, hWnd);

		// 시계 출력하기 
		clock->RenderClock(systemTime, hdc);

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:

		delete clock;
		delete hourToggle;
		delete minuteToggle;
		delete secondToggle;
		delete soundToggle;

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

// Animation.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Animation.h"
#include "resource.h"

#define MAX_LOADSTRING 100

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
	LoadStringW(hInstance, IDC_ANIMATION, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 애플리케이션 초기화를 수행합니다:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ANIMATION));

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

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ANIMATION));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_ANIMATION);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

bool MyIntersectRect(LPRECT rc1, LPRECT rc2)
{
	return((rc1->left < rc2->right&& rc1->right > rc2->left) &&
		(rc1->top < rc2->bottom&& rc1->bottom > rc2->top));
}
enum Dir { down, up, left, right };
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hMemDC;
	HDC hBackDC;
	HBITMAP hPlayerBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));
	HBITMAP hMapBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP3));
	BITMAP bit;
	static RECT rect;
	GetObject(hPlayerBitmap, sizeof(BITMAP), &bit);
	static RECT playerRect = { 0,0,400*0.2, 600*0.2 };
	static RECT enemyRect;
	static int nRenderNumberX = 0;
	static int nRenderNumberY = 0;

	switch (message)
	{
	case WM_CREATE:
	{
		hPlayerBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));
		hMapBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP3));
		SetTimer(hWnd, 1, 100, nullptr);
		nRenderNumberX = 0;
	}break;

	case WM_KEYDOWN:
	{
		if (wParam == VK_LEFT)
		{
			playerRect.left -= 8;
			playerRect.right -= 8;
			nRenderNumberY = Dir::left;
		}
		if (wParam == VK_RIGHT)
		{
			playerRect.left += 8;
			playerRect.right += 8;

			nRenderNumberY = Dir::right;
		}
		if (wParam == VK_DOWN)
		{
			playerRect.bottom += 8;
			playerRect.top += 8;

			nRenderNumberY = Dir::down;
		}
		if (wParam == VK_UP)
		{
			playerRect.bottom -= 8;
			playerRect.top -= 8;
			nRenderNumberY = Dir::up;
		}

		nRenderNumberX++;
		if (nRenderNumberX > 3) nRenderNumberX = 0;
		InvalidateRect(hWnd, nullptr, false);
		bool isC = MyIntersectRect(&enemyRect, &playerRect);
		if (playerRect.left < 0 || (isC && nRenderNumberY == Dir::left))
		{
			playerRect.left += 8;
			playerRect.right += 8;
		}
		else if (playerRect.left + 70 > rect.right || (isC && nRenderNumberY == Dir::right))
		{
			playerRect.left -= 8;
			playerRect.right -= 8;
		}
		else if (playerRect.top < 0 || (isC && nRenderNumberY == Dir::up))
		{
			playerRect.bottom += 8;
			playerRect.top += 8;
		}
		else if (playerRect.top + 100 > rect.bottom || (isC && nRenderNumberY == Dir::down))
		{
			playerRect.bottom -= 8;
			playerRect.top -= 8;
		}
	}break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		hBackDC = CreateCompatibleDC(hdc);
		hMemDC = CreateCompatibleDC(hdc);

		GetClientRect(hWnd, &rect);

		HBITMAP hBackBitmap = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
		HBITMAP oldBitmap = (HBITMAP)SelectObject(hBackDC, hBackBitmap);

		GetObject(hMapBitmap, sizeof(BITMAP), &bit);
		int bx = bit.bmWidth;
		int by = bit.bmHeight;

		oldBitmap = (HBITMAP)SelectObject(hMemDC, hMapBitmap);
		BitBlt(hBackDC, 0, 0, bx, by, hMemDC, 0, 0, SRCCOPY);
		SelectObject(hMemDC, oldBitmap);

		GetObject(hPlayerBitmap, sizeof(BITMAP), &bit);
		bx = bit.bmWidth / 4;
		by = bit.bmHeight / 4;

		oldBitmap = (HBITMAP)SelectObject(hMemDC, hPlayerBitmap);
		GdiTransparentBlt(hBackDC, playerRect.left, playerRect.top, bx * 0.2f, by * 0.2f, hMemDC, nRenderNumberX * bx, nRenderNumberY * by, bx, by, RGB(255, 0, 255));
		SelectObject(hMemDC, oldBitmap);

		bx = bit.bmWidth;
		by = bit.bmHeight;

		enemyRect.left = 500;
		enemyRect.top = 200;
		enemyRect.right = 700;
		enemyRect.bottom = 400;

		Rectangle(hBackDC, enemyRect.left, enemyRect.top, enemyRect.right, enemyRect.bottom);

		SelectObject(hMemDC, oldBitmap);

		BitBlt(hdc, 0, 0, rect.right, rect.bottom, hBackDC, 0, 0, SRCCOPY);

		SelectObject(hBackDC, oldBitmap);
		DeleteDC(hMemDC);
		DeleteDC(hBackDC);
		DeleteObject(hBackBitmap);
		EndPaint(hWnd, &ps);
	}
	break;

	case WM_DESTROY:
		DeleteObject(hPlayerBitmap);
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

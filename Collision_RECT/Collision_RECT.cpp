#include "framework.h"
#include "Collision_RECT.h"
#include "math.h"

#define MAX_LOADSTRING 100

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

	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_COLLISIONRECT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 애플리케이션 초기화를 수행합니다:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_COLLISIONRECT));

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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_COLLISIONRECT));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_COLLISIONRECT);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
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

bool MyIntersectCircle(RECT rc, RECT rc2)
{
	float rad1 = (rc.right - rc.left) / 2;
	float rad2 = (rc2.right - rc2.left) / 2;

	float deltaX = (rc.left + rad1) - (rc2.left + rad2);
	float deltaY = (rc.top + rad1) - (rc2.top + rad2);
	float distance = sqrt(pow(deltaX, 2) + pow(deltaY, 2));

	return (distance < rad1 + rad2);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static RECT Rect1 = { 50,50,150,150 };
	static RECT Rect2 = { 250,250,400,400 };
	static RECT rt;
	static bool isCollide;
	static RECT clientRect; 

	switch (message)
	{
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_UP:
			Rect1.top -= 5;
			Rect1.bottom -= 5;
			break;
		case VK_DOWN:
			Rect1.top += 5;
			Rect1.bottom += 5;
			break;
		case VK_LEFT:
			Rect1.left -= 5;
			Rect1.right -= 5;
			break;
		case VK_RIGHT:
			Rect1.left += 5;
			Rect1.right += 5;
			break;
		}

		if (MyIntersectCircle(Rect1, Rect2))
		{
			int a = 1;
			a = 2;
		}
		InvalidateRect(hWnd, nullptr, false);
	}break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		HDC hMemDC = CreateCompatibleDC(hdc);
		
		GetClientRect(hWnd, &clientRect);

		HBITMAP bitmap = CreateCompatibleBitmap(hdc, clientRect.right, clientRect.bottom);
		HBITMAP oldBitmap = (HBITMAP)SelectObject(hMemDC, bitmap);

		FillRect(hMemDC, &clientRect, (HBRUSH)GetStockObject(WHITE_BRUSH));

		Ellipse(hMemDC, Rect1.left, Rect1.top, Rect1.right, Rect1.bottom);
		Ellipse(hMemDC, Rect2.left, Rect2.top, Rect2.right, Rect2.bottom);

		if (isCollide)
		{
			HBRUSH hBrush = CreateSolidBrush(RGB(12, 215, 124));
			HBRUSH oldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);

			Rectangle(hMemDC, rt.left, rt.top, rt.right, rt.bottom);
			SelectObject(hMemDC, oldBrush);
			DeleteObject(hBrush);
		}

		BitBlt(hdc, 0, 0, clientRect.right, clientRect.bottom, hMemDC, 0, 0, SRCCOPY);
		
		SelectObject(hMemDC, oldBitmap);
		DeleteObject(bitmap);
		DeleteDC(hMemDC);
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

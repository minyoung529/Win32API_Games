// 21Winapi.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WinAPI_GameProgramming.h"
#include <math.h>
#include <vector>
#include <time.h>
#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
#define RECT_MAKE(x,y,s) { x-s/2, y-s/2, x+s/2, y+s/2}
#define RECT_DRAW(rt) Rectangle(hdc, rt.left, rt.top, rt.right, rt.bottom)

POINT g_ptMouse;

int delay = 50;
int score = 0;
int level = 0;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
POINT g_ptPos1 = { WINSIZEX / 2 , WINSIZEY - 85 };
RECT g_rtBox1;
struct tagBox
{
	RECT rt;
	float fSpeed;
};
vector<tagBox> vecBox;

enum class MOVE_DIR
{
	MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DONW
};
MOVE_DIR eMoveDir;
float fMoveSpeed = 20;

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
	LoadStringW(hInstance, IDC_WINAPIGAMEPROGRAMMING, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	srand((unsigned int)time(NULL));
	// 애플리케이션 초기화를 수행합니다:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPIGAMEPROGRAMMING));

	MSG msg;

	// 기본 메시지 루프입니다:

	// GetMessage > 대기
	// PeekMessage > 메세지를 받지 않은 상태에서!!
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		// msg.message == WM_QUIT 인 경우 프로그램 종료!
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg); // 입력에 대한 메시지 함수
			DispatchMessage(&msg);  // 메시지 전달
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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_WINAPIGAMEPROGRAMMING));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINAPIGAMEPROGRAMMING);
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
int Resolutionx = GetSystemMetrics(SM_CXSCREEN);
int Resolutiony = GetSystemMetrics(SM_CYSCREEN);

int Winposx = Resolutionx / 2 - WINSIZEX / 2;
int Winposy = Resolutiony / 2 - WINSIZEY / 2;
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	HWND hWnd = CreateWindowW(
		szWindowClass
		, szTitle
		, WS_OVERLAPPEDWINDOW
		, Winposx       // 윈도우 화면 좌측 상단 좌표 x
		, Winposy                   // 윈도우 화면 좌측 상단 좌표 y
		, WINSIZEX            // 윈도우 가로 사이즈
		, WINSIZEY                   // 윈도우 세로 사이즈
		, nullptr
		, nullptr
		, hInstance
		, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (message)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 10, NULL);
		srand((unsigned int)time(nullptr));
		break;

	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
	break;

	case WM_TIMER:
	{
		InvalidateRect(hWnd, nullptr, true);
		level = score / 100 + 1;
		g_rtBox1 = RECT_MAKE(g_ptPos1.x, g_ptPos1.y, 50);

		if (delay == 50)
		{
			tagBox box;
			box.rt.left = rand() % (WINSIZEX - 30);
			box.rt.right = box.rt.left + 30;
			box.rt.top = -30;
			box.rt.bottom = 0;

			box.fSpeed = rand() % 11 + 5;

			vecBox.push_back(box); // 비가 내리듯이 내릴거야.
			delay = rand() % 50;
		}
		else
			delay++;

		vector<tagBox>::iterator iter;

		for (iter = vecBox.begin(); iter != vecBox.end(); iter++)
		{
			iter->rt.top += iter->fSpeed;
			iter->rt.bottom += iter->fSpeed;

			RECT rt;
			RECT rtIter = iter->rt;

			if (iter->rt.top > WINSIZEY)
			{
				vecBox.erase(iter);
				score += 50;
				break;
			}

			if (IntersectRect(&rt, &g_rtBox1, &rtIter))
			{
				score -= 100;
				vecBox.erase(iter);
				break;
			}

			else if (PtInRect(&rtIter, g_ptMouse))
			{
				score += 300;
				vecBox.erase(iter);
				break;
			}
		}
	}
	break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);

		RECT_DRAW(g_rtBox1);

		for (int i = 0; i < vecBox.size(); i++)
		{
			RECT_DRAW(vecBox[i].rt);
		}

		char scoreBuffer[32];
		wchar_t levelBuffer[32];
		// 방법 1
		_itoa_s(score, scoreBuffer, 10);
		string str = string(scoreBuffer);
		TextOutA(hdc, 10, 10, str.c_str(), str.length());

		// 방법 2
		//wsprintf();	// api용
		swprintf_s(levelBuffer, L"레벨: %d", level);	// c 함수
		TextOut(hdc, 10, 30, levelBuffer, wcslen(levelBuffer));

		EndPaint(hWnd, &ps);
	}
	break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			g_ptPos1.x -= (g_rtBox1.left > 0) ? fMoveSpeed : 0;
			break;

		case VK_RIGHT:
			g_ptPos1.x += (g_rtBox1.right <= WINSIZEX - fMoveSpeed) ? fMoveSpeed : 0;
			break;
		}

		InvalidateRect(hWnd, nullptr, true);
		break;

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
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

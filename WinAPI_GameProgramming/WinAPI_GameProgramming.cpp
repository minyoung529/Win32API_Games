// 게임 프로그래밍 교과 과목으로 들은 Win32API 프로젝트
//

#include "framework.h"
#include "WinAPI_GameProgramming.h"
#include <vector>
#include <time.h>

#define MAX_LOADSTRING 100

#define RECT_MAKE(x, y, s) {x-s/2, y-s/2, x+s/2, y+s/2}
#define RECT_DRAW(rt) Rectangle(hdc, rt.left, rt.top, rt.right, rt.bottom)

// 전역 변수: 힙, 정적 변수와 같음, 데이터 영역
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

vector<RECT> vecBox;

POINT g_ptObjPos = { 500, 300 };
POINT g_ptObjScale = { 100,100 };

float moveSpeed = 20.f;
POINT pos = { WINSIZEX / 2,WINSIZEY - 30 };
RECT rtBox;

enum class MOVE_DIR
{
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_UP,
	MOVE_DOWN,
};

MOVE_DIR moveDir;

// 전방 선언 : 함수가 있음을 알리기 위함
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
bool				IsInCircle(LONG x, LONG y, LONG circleX, LONG circleY, int radius);

// 물리메모리 주소는 다르지만, 가상메모리 주소는 같아서 instance 값이 같음
// 따라서 PrevInstnace가 필요 없어짐!

// 윈도우 만들고, 메세지를 전송함
int APIENTRY wWinMain(/*이거 입력되는 인자임 >*/ _In_ HINSTANCE hInstance,
	/*이거 필요 없음 >*/       _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	/*윈도우가 보일지 안 보일지*/_In_ int       nCmdShow)
{
	// 이거 필요 없음
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WINAPIGAMEPROGRAMMING, szWindowClass, MAX_LOADSTRING);

	// 창 등록
	MyRegisterClass(hInstance);

	// 창 만들고 보여주고 업데이트!
	// 애플리케이션 초기화를 수행합니다:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	// 메뉴 단축키화
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPIGAMEPROGRAMMING));

	MSG msg;
	//msg.message == WM_QUIT인 경우 프로그램 종료!

	// ** 기본 메시지 루프! **
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		// 단축키 안 쓸 거면 조건문 없애도 된다
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);

			// WndProc로 메세지 전달함
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
	// 윈도우 구조체
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;                                          // 가로 세로 달라지면 다시 그리겠다는 뜻

	wcex.lpfnWndProc = WndProc;                                                          // 콜백 함수, 운영체제가 호출함
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;                                                        // 프로그램의 주소
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPIGAMEPROGRAMMING));
	wcex.hCursor = LoadCursor(nullptr, IDC_CROSS);                                   // 커서 아이콘
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);/*GetStockObject(BLACK_BRUSH);*/        // 배경 색
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINAPIGAMEPROGRAMMING);                      // 위에 메뉴 (파일, 도움말) nullptr로 바꾸면 없어짐!
	wcex.lpszClassName = szWindowClass;                                                    // 클래스 이름 (윈도우창의 이름?)
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));             // 작은 아이콘

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

int resolutionX = GetSystemMetrics(SM_CXSCREEN);
int resolutionY = GetSystemMetrics(SM_CYSCREEN);

int winPosX = (resolutionX - WINSIZEX) / 2;
int winPosY = (resolutionY - WINSIZEY) / 2;

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	// 윈도우 창 만들어짐
	HWND hWnd = CreateWindowW
	(
		szWindowClass,           // 키 값
		szTitle,
		WS_OVERLAPPEDWINDOW,     // 윈도우 스타일
		winPosX,                 // 중요! 윈도우 화면 좌측 상단 좌표 X
		winPosY,                 // 윈도우 화면 좌측 상단 좌표 y
		WINSIZEX,                // 윈도우 가로 사이즈
		WINSIZEY,                // 세로 사이즈
		nullptr,
		nullptr,
		hInstance,
		nullptr
	);

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
	static bool flag = false;
	static int x = 0, y = 0;
	int radius = 30;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT: // 무효화 영역 (Invalidate Rect)
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		for (int i = 0; i < vecBox.size(); i++)
		{
			RECT_DRAW(vecBox[i]);
		}

		EndPaint(hWnd, &ps);
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		HideCaret(hWnd);
		DestroyCaret();
		KillTimer(hWnd, 1);
		break;

	case WM_TIMER:
	{
		InvalidateRect(hWnd, nullptr, true);

		rtBox = RECT_MAKE(pos.x, pos.y, 50);
		RECT rt;
		rt.left = rand() % WINSIZEX - 30;
		rt.right = rt.left += 30;

		rt.top = -30;
		rt.bottom = 0;

		vecBox.push_back(rt);

		for (int i = 0; i < vecBox.size(); i++)
		{
			vecBox[i].top += 10;
			vecBox[i].bottom += 10;
		}
	}break;

	case WM_MOUSEMOVE:
	{
		if (flag)
		{
			x = LOWORD(lParam);
			y = HIWORD(lParam);
			InvalidateRect(hWnd, nullptr, true);
		}
	}

	case WM_CREATE:
		CreateCaret(hWnd, NULL, 2, 15);
		ShowCaret(hWnd);
		srand((unsigned int)time(nullptr));
		SetTimer(hWnd, 1, 50, nullptr);
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

bool IsInCircle(LONG x, LONG y, LONG circleX, LONG circleY, int radius)
{
	//float dist = sqrt(pow(x, 2) - pow(circleX, 2) + pow(y, 2) - pow(circleY, 2));
	float dist = sqrt(pow(y - circleY, 2) + pow(x - circleX, 2));

	return (dist <= radius);
}
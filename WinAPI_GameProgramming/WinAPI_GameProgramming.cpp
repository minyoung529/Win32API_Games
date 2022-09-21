// 게임 프로그래밍 교과 과목으로 들은 Win32API 프로젝트
//

#include "framework.h"
#include "WinAPI_GameProgramming.h"

#define MAX_LOADSTRING 100

// 전역 변수: 힙, 정적 변수와 같음, 데이터 영역
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

POINT g_ptObjPos = { 500, 300 };
POINT g_ptObjScale = { 100,100 };

POINT memoPos = { 0,0 };

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
	//static wstring str;
	static wchar_t str[120];
	static int count = 0, yPos = 0, endlCnt = 0;
	static RECT rt = { 0,0,1000,1000 };
	static SIZE size;
	static bool flag = false;

	static int x, y;

	static RECT rtView;
	HDC hdc;

	switch (message)
	{
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

	// 커널 오브젝트 (운영체제가 관리하는 객체, 제어 불가)
	// -> 핸들을 가지고 아이디값을 가져와서 제어

	// H가 붙은 건 모두 핸들
	case WM_PAINT: // 무효화 영역 (Invalidate Rect)
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		// 숙제
		/*
		wchar_t temp[MAX_LINE + 1];
		int endlIndex = 0;

		for (int i = 0; i < 110; i++)
		{
			if (str[i] == '\n')
				endlIndex = i + 1;
		}

		for (int i = 0; i <= MAX_LINE; i++)
		{
			temp[i] = str[i + endlIndex];
		}

		DrawText(hdc, str, wcslen(str), &rt, DT_TOP | DT_LEFT);
		GetTextExtentPoint(hdc, temp, wcslen(temp), &size);

		if (temp[0] == NULL)
			SetCaretPos(0, endlCnt * 16);
		else
			SetCaretPos(size.cx, endlCnt * size.cy);

		Ellipse(hdc, x - 20, y - 20, x + 20, y + 20);
		*/
		/*

		// DC 만들어서 그 ID를 반환

		// 커널 오브젝트를 가져오기 위해서~ divice context
		// ID 중복을 피하기 위해서 핸들이 많다

		// 기본 펜은 검은색, 기본 브러쉬는 하얀색

		// 펜 만들어서 DC에 지급

		//
		//HPEN pen = CreatePen(PS_SOLID, 5, RGB(255, 143, 160));
		//HPEN oldPen = (HPEN)SelectObject(hdc, pen);

		//HBRUSH brush = CreateSolidBrush(RGB(254, 255, 92));
		//HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

		//// 사각형 출력
		//Rectangle(hdc, 10, 10, 110, 100); // 그리기

		//// TextOut
		//wstring wstr = L"안뇽";
		//TextOut(hdc, 200, 200, wstr.c_str(), wstr.length());

		//// DrawText
		//RECT rect = { 300, 300, 400, 400 };

		//DrawText(hdc, L"안녕, 세상아!", 9, &rect, DT_SINGLELINE | DT_RIGHT);

		//// 선 그리기
		//MoveToEx(hdc, 100, 500, nullptr);
		//LineTo(hdc, 300, 0);

		//Ellipse(hdc, 50, 50, 150, 150);

		//// 클라이언트 영역 재조정
		//rect = { winPosX, winPosY, winPosX + WINSIZEX, winPosY + WINSIZEY };
		//AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, TRUE);
		//MoveWindow(hWnd, winPosX, winPosY, rect.right - rect.left, rect.bottom - rect.top, TRUE);

		//// 16 x 9 격자 그리기
		//for (int x = 0; x <= WINSIZEX; x += WINSIZEX / 16)
		//{
		//	MoveToEx(hdc, x, WINSIZEY, nullptr);
		//	LineTo(hdc, x, 0);
		//}

		//for (int y = 0; y <= WINSIZEY; y += WINSIZEY / 9)
		//{
		//	MoveToEx(hdc, WINSIZEX, y, nullptr);
		//	LineTo(hdc, 0, y);
		//}

		//int left = 100;
		//int top = 100;

		//for (int i = 0; i < 25; i++)
		//{
		//	if (i % 5 == 0 && i != 0)
		//	{
		//		left = 100;
		//		top += 70;
		//	}

		//	if ((i / 5) % 2 == 0)
		//	{
		//		Rectangle(hdc, left, top, left + 50, top + 50);
		//	}
		//	else
		//	{
		//		Ellipse(hdc, left, top, left + 50, top + 50);
		//	}

		//	left += 70;
		//}

		//DeleteObject(pen);
		//DeleteObject(brush);
		//SelectObject(hdc, oldPen);
		//*/

		HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));

		if (flag)
		{
			//SelectObject(hdc, hBlueBrush);
			Rectangle(hdc, x - 20, y - 20, x + 20, y + 20);
		}

		Ellipse(hdc, x - 20, y - 20, x + 20, y + 20);

		/*Rectangle(hdc,
			g_ptObjPos.x - g_ptObjScale.x / 2, g_ptObjPos.y - g_ptObjScale.y / 2,
			g_ptObjPos.x + g_ptObjScale.x / 2, g_ptObjPos.y + g_ptObjScale.y / 2);*/

		EndPaint(hWnd, &ps);
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		HideCaret(hWnd);
		DestroyCaret();
		KillTimer(hWnd, 1);
		break;

	case WM_KEYDOWN:
	{
		SetTimer(hWnd, 1, 100, NULL);
	}break;

	case WM_TIMER:
		x += 40;
		if (x + 20 > rtView.right)
		{
			x -= 40;
		}
		InvalidateRect(hWnd, nullptr, true);
		break;

	case WM_LBUTTONDOWN:
	{
		int mx = LOWORD(lParam);
		int my = HIWORD(lParam);

		if (IsInCircle(mx, my, x, y, 40))
			flag = true;
		else
			flag = false;

		InvalidateRect(hWnd, nullptr, true);
	}break;

	case WM_KEYUP:
		flag = false;
		InvalidateRect(hWnd, nullptr, true);
		break;

		// 문자 입력시
	case WM_CHAR:
	{
		hdc = GetDC(hWnd);

		/*
		if (wParam == VK_BACK && count > 0)
		{
			str[count--] = NULL;

			if (str[count] == '\n')
			{
				endlCnt--;
			}
		}
		else
		{
			if (((count - endlCnt) >= MAX_LINE && (count - endlCnt) % MAX_LINE == 0) || wParam == VK_RETURN)
			{
				if (endlCnt >= MAX_LINE - 1)
					break;

				if (wParam != VK_RETURN)
				{
					str[count++] = '\n';
				}

				endlCnt++;
			}

			if (wParam != VK_RETURN)
				str[count++] = wParam;
			else
				str[count++] = '\n';
		}

		str[count] = NULL;
		*/
		InvalidateRect(hWnd, nullptr, true);
		ReleaseDC(hWnd, hdc);
	}break;

	case WM_CREATE:
		count = yPos = 0;
		x = y = 20;
		CreateCaret(hWnd, NULL, 2, 15);
		ShowCaret(hWnd);

		GetClientRect(hWnd, &rtView);
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
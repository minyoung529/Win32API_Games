#include "framework.h"
#include "Tetris.h"

#define MAX_LOADSTRING		100
#define random(n)			(rand()%n)

HINSTANCE hInst;
HWND g_hWnd;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void				leftMove();
void				rightMove();
int					downMove();
void				rotate();
void				brick(int flag);
void				drawscreen();
void				drawNextBrick();
void				isFull();
int					whataround(int x, int y);


int pat[7][32] =
{
	{0,0, 1,0, 2,0, -1,0,    0,0, 0,1, 0,-1, 0,-2, },
	{0,0, 1,0, 0,1, 1,1,},
	{0,0, -1,0, 0,-1, 1,-1,  0,0, 0,1, -1,0, -1,-1,},
	{0,0, -1,-1, 0,-1, 1,0,  0,0, -1,0, -1,1, 0,-1,},
	{0,0, 0,-1, 1,0, 2,0,    0,0, -1,0, 0,-1, 0,-2, 0,0, -1,0, -2,0, 0,1,  0,0, 1,0, 0,1, 0,2},
	{0,0, -1,0, -2,0, 0,-1,  0,0, -1,0, 0,1, 0,2,   0,0, 0,1, 1,0, 2,0,    0,0, 1,0, 0,-1, 0,-2},
	{0,0, -1,0, 1,0, 0,1,    0,0, 0,-1, 0,1, 1,0,   0,0, -1,0, 1,0, 0,-1,  0,0, -1,0, 0,-1, 0,1},
};

int brickpatnum[7] = { 2,1,2,2,4,4,4 };
int tet[14][23];
int score;
int speed;
int nowBrick, nowRotate;
int nextbrick;
int nowX, nowY;
bool bGameStart;
TCHAR tempStr[128];

HDC hBrickDC, hBlankDC; //처음부터 손에 쥐고 있다

HBITMAP hBrickBitmap;
HBITMAP hBlankBitmap;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));
	MSG msg;

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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 500, 500, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	g_hWnd = hWnd;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;

		case ID_START:
			for (int i = 0; i < 14; i++)
			{
				for (int j = 0; j < 23; j++)
				{
					if (i == 0 || i == 13 || j == 22)
						tet[i][j] = 2;
					else
						tet[i][j] = 0;
				}
			}
			speed = 500;
			score = 0;
			bGameStart = true;

			nextbrick = random(7);
			SetTimer(hWnd, 1, speed, nullptr);

			InvalidateRect(hWnd, nullptr, true);
			UpdateWindow(hWnd);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;

	case WM_CREATE:
	{
		HDC hDC = GetDC(hWnd);
		hBrickDC = CreateCompatibleDC(hDC);
		hBlankDC = CreateCompatibleDC(hDC);

		hBrickBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BRICK));
		hBlankBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BLANK));

		SelectObject(hBrickDC, hBrickBitmap);
		SelectObject(hBlankDC, hBlankBitmap);

		ReleaseDC(hWnd, hDC);

		bGameStart = false;
		srand(GetTickCount64());

	}return 0;

	case WM_KEYDOWN:
	{
		if (!bGameStart) return 0;

		switch (wParam)
		{
		case VK_LEFT:
			leftMove();
			break;

		case VK_RIGHT:
			rightMove();
			break;

		case VK_DOWN:
			downMove();
			break;

		case VK_UP:
			rotate();
			break;
		}
		return 0;
	}break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		drawscreen();
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

void leftMove()
{
	if (whataround(nowX - 1, nowY) != 0) return;
	brick(0);
	--nowX;
	brick(1);
}

void rightMove()
{
	if (whataround(nowX + 1, nowY) != 0) return;

	brick(0);
	++nowX;
	brick(1);
}

int downMove()
{
	if (whataround(nowX, nowY + 1) != 0)
	{
		isFull();
		return 1;
	}

	brick(0);
	++nowY;
	brick(1);
	return 1;
}

void rotate()
{
	int temp1, temp2;
	temp1 = nowRotate;
	nowRotate++;

	if (nowRotate == brickpatnum[nowBrick]) nowRotate = 0;

	temp2 = nowRotate;
	nowRotate = temp1;
	brick(0);
	nowRotate = temp2;
	brick(1);
}

int whataround(int x, int y)
{
	int k = 0;

	for (int i = 0; i < 4; i++)
	{
		int j = tet[x + pat[nowBrick][nowRotate * 8 + i]]
			[y + pat[nowBrick][nowRotate * 8 + i]];

		if (j < k)
			k = j;
	}

	return k;
}

void brick(int flag)
{
	HDC tempDC;
	HDC hDC = GetDC(g_hWnd);

	if (flag == 0)
		tempDC = hBlankDC;
	else
		tempDC = hBrickDC;

	for (int i = 0; i < 4; i++)
	{
		BitBlt(hDC, (nowX + pat[nowBrick][nowRotate * 8 + i * 2]) * 20,
			(nowY + pat[nowBrick][nowRotate * 8 + i * 2 + 1]) * 20,
			20, 20, tempDC, 0, 0, SRCCOPY);
	}

	ReleaseDC(g_hWnd, hDC);
}

void drawscreen()
{
	HDC tempDC;
	HDC hDC = GetDC(g_hWnd);

	Rectangle(hDC, 18, 18, 262, 422);
	Rectangle(hDC, 270, 18, 470, 150);
	TextOut(hDC, 290, 30, TEXT("경기게임마이스터고"), 9);

	wsprintf(tempStr, TEXT("점수: %d"), score);
	TextOut(hDC, 270, 200, tempStr, lstrlen(tempStr));

	for (int i = 1; i < 13; i++)
	{
		for (int j = 1; j < 21; j++)
		{
			if (tet[i][j] == 1)
				tempDC = hBrickDC;
			else
				tempDC = hBlankDC;

			BitBlt(hDC, i * 20, j * 20, 20, 20, tempDC, 0, 0, SRCCOPY);
		}
	}

	drawNextBrick();
	ReleaseDC(g_hWnd, hDC);
}

void drawNextBrick()
{
	HDC hDC = GetDC(g_hWnd);
	RECT rect = { 271,321,469,419 };
	Rectangle(hDC, rect.left - 1, rect.top - 1, rect.right + 1, rect.bottom + 1);

	if (!bGameStart) return;

	FillRect(hDC, &rect, (HBRUSH)(GetStockObject(WHITE_BRUSH)));

	for (int i = 0; i < 4; i++)
	{
		BitBlt(hDC, (17 + pat[nextbrick][i * 2]) * 20,
			(18 + pat[nextbrick][i * 2 + 1]) * 20,
			20, 20, hBrickDC, 0, 0, SRCCOPY);
	}

	ReleaseDC(g_hWnd, hDC);
}

void isFull()
{
	int check, check2;
	score++;
	for (int i = 0; i < 4; i++)
	{
		tet[nowX + pat[nowBrick][nowRotate * 8 + i * 2]][nowX + pat[nowBrick][nowRotate * 8 + i * 2 + 1]] = 1;
	}
	check2 = 0;

	for (int i = 1; i < 20; i++)
	{
		check = 0;
		for (int j = 20; j > 0; j--)
			if (tet[i][j] == 0)
				check = 1;

		if (check == 0)
		{
			check2 = 1;
			for (int k = i - 1; k > 0; k--)
				for (int j = 1; j < 13; j++)
					tet[j][k + 1] = tet[j][k];
			i++;
		}
	}

	if (check2 == 0) return;
	score += 10;
	KillTimer(g_hWnd, 1);
	speed -= 10;
	if (speed < 100) speed = 100;
	SetTimer(g_hWnd, 1, speed, nullptr);
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

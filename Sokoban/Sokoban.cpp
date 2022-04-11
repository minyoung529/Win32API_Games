// Sokoban.cpp : 애플리케이션에 대한 진입점을 정의합니다.
#include "framework.h"
#include "Sokoban.h"
#include <string>
using namespace std;

#define MAX_LOADSTRING 100

// 그림의 크기와 타일 개수 / 윈도우 사이즈
#define X_SIZE          32
#define Y_SIZE          32
#define X_BLOCK         18
#define Y_BLOCK         13
#define X_CORRECT       16
#define Y_CORRECT       58
#define WIN_WIDTH       X_SIZE * X_BLOCK + X_CORRECT
#define WIN_HEIGHT      Y_SIZE * Y_BLOCK + Y_CORRECT

// 타일맵 문자
#define TILE            '#'
#define TUTA            '@'
#define ROAD            ' '
#define BOX             'B'
#define GOAL            'X'

// 맵 정보
#define MAXSTAGE        2

void					Stage_Change(unsigned int);

//현재 선택된 맵
unsigned char ucMap[Y_BLOCK][X_BLOCK + 1];

unsigned char ucStageMap[MAXSTAGE][Y_BLOCK][X_BLOCK + 1] = {
	{
		"##################",
		"##################",
		"##################",
		"##################",
		"##################",
		"##################",
		"##  ##############",
		"#  B#########   @#",
		"#   # ## ####    #",
		"#       B       X#",
		"##### ### # #   X#",
		"#####     ########",
		"##################"
	},
	{
		"##################",
		"##################",
		"##################",
		"#####   ##########",
		"#####B  ##########",
		"#####  B##########",
		"###  B B #########",
		"### # ## #########",
		"#   # ## ####  XX#",
		"# B  B   @     XX#",
		"##### ### # #  XX#",
		"#####     ########",
		"##################"
	}
};

unsigned int ucStageCount[MAXSTAGE] = { 100,300 };

HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND g_hWnd;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

static HBITMAP SELBitmap;
static HBITMAP CharacterDown;
static HBITMAP CharacterUp;
static HBITMAP CharacterLeft;
static HBITMAP CharacterRight;
static HBITMAP Tile;
static HBITMAP Road;
static HBITMAP Box;
static HBITMAP Goal;

unsigned int uiStage;

int iMap_X;		//character Position.x
int iMap_Y;		//character Position.y

unsigned int uiM_Count; // goal count
unsigned int uiMatch;	// cur goal count

unsigned int uiKeyCount = 0;

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

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_SOKOBAN, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 애플리케이션 초기화를 수행합니다:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SOKOBAN));

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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SOKOBAN));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_SOKOBAN);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, WIN_WIDTH, WIN_HEIGHT, nullptr, nullptr, hInstance, nullptr);

	g_hWnd = hWnd;
	if (!g_hWnd)
	{
		return FALSE;
	}

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		CharacterDown = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		CharacterUp = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));
		CharacterLeft = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP3));
		CharacterRight = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP4));

		Tile = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP5));
		Road = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP6));
		Box = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP7));
		Goal = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP8));

		uiStage = 0;
		Stage_Change(uiStage);
	}break;

	case WM_KEYDOWN:
	{
		RECT rc;
		rc.left = iMap_X * X_SIZE;
		rc.right = rc.left + X_SIZE;
		rc.top = iMap_Y * Y_SIZE;
		rc.bottom = rc.top + Y_SIZE;

		switch (wParam)
		{
		case VK_LEFT:
			uiKeyCount++;
			SELBitmap = CharacterLeft;
			if (ucMap[iMap_Y][iMap_X - 1] != TILE)
			{
				rc.left -= X_SIZE;
				if (ucMap[iMap_Y][iMap_X - 1] == BOX)
				{
					if (ucMap[iMap_Y][iMap_X - 2] == ROAD)
					{
						rc.left -= X_SIZE;
						ucMap[iMap_Y][iMap_X - 2] = BOX;
					}
					else
					{
						break;
					}
				}
				ucMap[iMap_Y][iMap_X] = ROAD;
				ucMap[iMap_Y][--iMap_X] = TUTA;
			}
			break;
		case VK_RIGHT:
			uiKeyCount++;

			SELBitmap = CharacterRight;

			if (ucMap[iMap_Y][iMap_X + 1] != TILE)
			{
				rc.right += X_SIZE;
				if (ucMap[iMap_Y][iMap_X + 1] == BOX)
				{
					if (ucMap[iMap_Y][iMap_X + 2] == ROAD)
					{
						rc.right += X_SIZE;
						ucMap[iMap_Y][iMap_X + 2] = BOX;
					}
					else
					{
						break;
					}
				}
				ucMap[iMap_Y][iMap_X] = ROAD;
				ucMap[iMap_Y][++iMap_X] = TUTA;
			}

			break;
		case VK_UP:
			uiKeyCount++;

			SELBitmap = CharacterUp;
			if (ucMap[iMap_Y - 1][iMap_X] != TILE)
			{
				rc.top -= Y_SIZE;
				if (ucMap[iMap_Y - 1][iMap_X] == BOX)
				{
					if (ucMap[iMap_Y - 2][iMap_X] == ROAD)
					{
						rc.top -= Y_SIZE;
						ucMap[iMap_Y - 2][iMap_X] = BOX;
					}
					else
					{
						break;
					}
				}
				ucMap[iMap_Y][iMap_X] = ROAD;
				ucMap[--iMap_Y][iMap_X] = TUTA;
			}
			break;
		case VK_DOWN:
			uiKeyCount++;

			SELBitmap = CharacterDown;
			if (ucMap[iMap_Y + 1][iMap_X] != TILE)
			{
				rc.bottom += Y_SIZE;
				if (ucMap[iMap_Y + 1][iMap_X] == BOX)
				{
					if (ucMap[iMap_Y + 2][iMap_X] == ROAD)
					{
						rc.bottom += Y_SIZE;
						ucMap[iMap_Y + 2][iMap_X] = BOX;
					}
					else
					{
						break;
					}
				}
				ucMap[iMap_Y][iMap_X] = ROAD;
				ucMap[++iMap_Y][iMap_X] = TUTA;
			}
		}

		if (uiKeyCount >= ucStageCount[uiStage])
		{
			if (MessageBox(hWnd, TEXT("현준아 안뇽~~??ㅎㅎ"), TEXT("GAMEOVER"), MB_OK) == IDOK)
			{
				Stage_Change(uiStage);
				break;
			}
		}

		InvalidateRect(g_hWnd, &rc, false);
	}break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		HDC hMemDC = CreateCompatibleDC(hdc);
		uiM_Count = 0;

		for (int i = 0; i < Y_BLOCK; i++)
		{
			for (int j = 0; j < X_BLOCK; j++)
			{
				if (ucMap[i][j] == TILE)
				{
					SelectObject(hMemDC, Tile);
				}
				else if (ucMap[i][j] == TUTA)
				{
					SelectObject(hMemDC, SELBitmap);
				}
				else if (ucMap[i][j] == BOX)
				{
					SelectObject(hMemDC, Box);
					if (ucStageMap[uiStage][i][j] == GOAL)
						uiM_Count++;
				}
				else if (ucStageMap[uiStage][i][j] == GOAL)
				{
					SelectObject(hMemDC, Goal);
				}
				else
				{
					SelectObject(hMemDC, Road);
				}

				BitBlt(hdc, j * X_SIZE, i * Y_SIZE, X_SIZE, Y_SIZE, hMemDC, 0, 0, SRCCOPY);
			}
		}

		if (uiMatch == uiM_Count)
		{
			Stage_Change(++uiStage);
			InvalidateRect(hWnd, nullptr, true);
		}
				
		TCHAR str[128];
		wsprintf(str, TEXT("이동횟수 %d"), uiKeyCount);
		TextOut(hdc, 0, 0, str, lstrlen(str));

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

void Stage_Change(unsigned int stage)
{
	uiStage = stage % MAXSTAGE;
	uiKeyCount = 0;
	uiMatch = 0;
	SELBitmap = CharacterDown;

	for (int i = 0; i < Y_BLOCK; i++)
	{
		for (int j = 0; j < X_BLOCK; j++)
		{
			if (ucStageMap[uiStage][i][j] == TUTA)
			{
				iMap_X = j;
				iMap_Y = i;
			}

			ucMap[i][j] = ucStageMap[uiStage][i][j];

			if (ucStageMap[uiStage][i][j] == GOAL)
			{
				ucMap[i][j] = ROAD;
				uiMatch++;
			}
		}
	}

	InvalidateRect(g_hWnd, nullptr, true);
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

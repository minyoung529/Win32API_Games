#include "framework.h"
#include "Omok.h"
#include <math.h>

#define MAX_LOADSTRING  100

#define X_COUNT         19
#define Y_COUNT         19

// one cell interval
#define INTERVAL        26
#define HALFINTERVAL    INTERVAL/2

#define START_X         50
#define START_Y         50

//Macro
#define XPOS(x)			(START_X + (x) * INTERVAL)
#define YPOS(y)			(START_Y + (y) * INTERVAL)

HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

unsigned char board[X_COUNT][Y_COUNT];
enum OMOKPIECE { NONE, BLACK_DOL, WHITE_DOL };

// black => true, white => false
bool turn = true;
int pieceCount = 0;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void OnPaint(HWND hWnd, HDC hdc);
void OnLButtonDown(HWND hWnd, int x, int y);
char CheckWinCondition();
void Reset(HWND hWnd);
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
	LoadStringW(hInstance, IDC_OMOK, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 애플리케이션 초기화를 수행합니다:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OMOK));

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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OMOK));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_OMOK);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		50, 50, 600, 600, nullptr, nullptr, hInstance, nullptr);

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
	case WM_LBUTTONDOWN:
	{
		int mouseX = LOWORD(lParam);
		int mouseY = HIWORD(lParam);

		OnLButtonDown(hWnd, mouseX, mouseY);
	}break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		if (IsGameOver() != 0)
		{

		}
		OnPaint(hWnd, hdc);
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

void OnPaint(HWND hWnd, HDC hdc)
{
#pragma region Background
	HBRUSH hBrush = CreateSolidBrush(RGB(244, 176, 77));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	RECT backgroundRect;
	GetClientRect(hWnd, &backgroundRect);

	FillRect(hdc, &backgroundRect, hBrush);

	SelectObject(hdc, oldBrush);
	DeleteObject(hBrush);
#pragma endregion
#pragma region MyRegion
	for (int x = 0; x < X_COUNT; x++)
	{
		MoveToEx(hdc, XPOS(x), YPOS(0), nullptr);
		LineTo(hdc, XPOS(x), YPOS(Y_COUNT - 1));
	}

	for (int y = 0; y < Y_COUNT; y++)
	{
		MoveToEx(hdc, XPOS(0), YPOS(y), nullptr);
		LineTo(hdc, XPOS(X_COUNT - 1), YPOS(y));
	}
#pragma endregion

	for (int y = 0; y < Y_COUNT; y++)
	{
		for (int x = 0; x < X_COUNT; x++)
		{
			if (board[y][x] > 0)
			{
				if (board[y][x] == BLACK_DOL)
					SelectObject(hdc, GetStockObject(BLACK_BRUSH));
				else
					SelectObject(hdc, GetStockObject(WHITE_BRUSH));

				Ellipse(hdc, XPOS(x) - HALFINTERVAL, YPOS(y) - HALFINTERVAL, XPOS(x) + HALFINTERVAL, YPOS(y) + HALFINTERVAL);
			}
		}
	}
}

void OnLButtonDown(HWND hWnd, int mouseX, int mouseY)
{
	if (mouseX > XPOS(0) - HALFINTERVAL && mouseY > YPOS(0) - HALFINTERVAL &&
		mouseX < XPOS(X_COUNT - 1) + HALFINTERVAL && mouseY < YPOS(Y_COUNT - 1) + HALFINTERVAL)
	{
		int x = (mouseX - START_X + HALFINTERVAL) / INTERVAL;
		int y = (mouseY - START_Y + HALFINTERVAL) / INTERVAL;

		if (board[y][x] == NONE)
		{
			if (turn == true)
				board[y][x] = BLACK_DOL;
			else
				board[y][x] = WHITE_DOL;

			turn = !turn;

			pieceCount++;

			InvalidateRect(hWnd, nullptr, true);

			char result = CheckWinCondition();

			if (result == -1)
			{
				if (IDOK == MessageBox(hWnd, TEXT("꽉 찼습니다."), TEXT("게임 종료!"), MB_OK))
					Reset(hWnd);
			}
			else if (result == BLACK_DOL)
			{
				if (IDOK == MessageBox(hWnd, TEXT("검은 돌 이겼습니다."), TEXT("게임 종료!"), MB_OK))
					Reset(hWnd);
			}
			else if (result == WHITE_DOL)
			{
				if (IDOK == MessageBox(hWnd, TEXT("하얀 돌 이겼습니다."), TEXT("게임 종료!"), MB_OK))
					Reset(hWnd);
			}
		}
	}
}

// 선생님께서 쓰신 코드
bool IsGameOver()
{
	for (int y = 0; y < Y_COUNT; y++)
	{
		for (int x = 0; x < X_COUNT; y++)
		{
			if (board[y][x] == 0) continue;

			if (x < X_COUNT - 4 &&
				board[y][x] == board[y][x + 1] &&
				board[y][x + 1] == board[y][x + 2] &&
				board[y][x + 2] == board[y][x + 3] &&
				board[y][x + 3] == board[y][x + 4])
			{
				if (board[y][x] == BLACK_DOL || board[y][x] == WHITE_DOL)
					return 1;
			}

			if (y < Y_COUNT - 4 &&
				board[y][x] == board[y + 1][x] &&
				board[y + 1][x] == board[y + 2][x] &&
				board[y + 2][x] == board[y + 3][x] &&
				board[y + 3][x] == board[y + 4][x])
			{
				if (board[y][x] == BLACK_DOL || board[y][x] == WHITE_DOL)
					return 1;
			}

			if (y < Y_COUNT - 4 && x < X_COUNT - 4 &&
				board[y][x] == board[x + 1][y + 1] &&
				board[x + 1][y + 1] == board[x + 2][y + 2] &&
				board[y + 2][x + 2] == board[x + 3][y + 3] &&
				board[y + 3][x + 3] == board[x + 4][y + 4])
			{
				if (board[y][x] == BLACK_DOL || board[y][x] == WHITE_DOL)
					return 1;
			}

			if (y >= 4 && x < X_COUNT - 4 &&
				board[y][x] == board[y - 1][x + 1] &&
				board[y - 1][x + 1] == board[y - 2][x + 2] &&
				board[y - 2][x + 2] == board[y - 3][x + 3] &&
				board[y - 3][x + 3] == board[y - 4][x + 4])
			{
				if (board[y][x] == BLACK_DOL || board[y][x] == WHITE_DOL)
					return 1;
			}

			if (y < Y_COUNT - 4 && x < X_COUNT - 4 &&
				board[y][x] == board[x + 1][y + 1] &&
				board[x + 1][y + 1] == board[x + 2][y + 2] &&
				board[y + 2][x + 2] == board[x + 3][y + 3] &&
				board[y + 3][x + 3] == board[x + 4][y + 4])
			{
				if (board[y][x] == BLACK_DOL || board[y][x] == WHITE_DOL)
					return 1;
			}

			if (pieceCount >= X_COUNT * Y_COUNT)
			{
				return 1;
			}
		}
	}

	return 0;
}

char CheckWinCondition()
{
	if (pieceCount >= X_COUNT * Y_COUNT) return -1;

	else
	{
		int bCount = 0;
		int wCount = 0;

		for (int y = 0; y < Y_COUNT; y++)
		{
			for (int x = 0; x < X_COUNT; x++)
			{
				if (board[y][x] == BLACK_DOL)
					bCount++;
				else
					bCount = 0;

				if (board[y][x] == WHITE_DOL)
					wCount++;
				else
					wCount = 0;

				if (bCount >= 5) return BLACK_DOL;
				else if (wCount >= 5) return WHITE_DOL;
			}

			bCount = 0;
			wCount = 0;
		}

		for (int x = 0; x < X_COUNT; x++)
		{
			for (int y = 0; y < Y_COUNT; y++)
			{
				if (board[y][x] == BLACK_DOL)
					bCount++;
				else
					bCount = 0;

				if (board[y][x] == WHITE_DOL)
					wCount++;
				else
					wCount = 0;

				if (bCount >= 5) return BLACK_DOL;
				else if (wCount >= 5) return WHITE_DOL;
			}

			bCount = 0;
			wCount = 0;
		}

		//대각선..ㅠ
		for (int x = 0; x < X_COUNT - 3; x++)
		{
			for (int y = 0, b2Cnt = 0, w2Cnt = 0; y < Y_COUNT; y++)
			{
				if (board[y][x + y] == BLACK_DOL)
					bCount++;
				else
					bCount = 0;

				if (board[y][x + y] == WHITE_DOL)
					wCount++;
				else
					wCount = 0;

				if (board[y][X_COUNT - 1 - x - y] == BLACK_DOL)
					b2Cnt++;
				else
					b2Cnt = 0;

				if (board[y][X_COUNT - 1 - x - y] == WHITE_DOL)
					w2Cnt++;
				else
					w2Cnt = 0;

				if (bCount >= 5 || b2Cnt >= 5) return BLACK_DOL;
				else if (wCount >= 5 || w2Cnt >= 5) return WHITE_DOL;
			}
		}

		for (int y = 0; y < Y_COUNT - 3; y++)
		{
			for (int x = 0, b2Cnt = 0, w2Cnt = 0; x < X_COUNT; x++)
			{
				if (board[y + x][x] == BLACK_DOL)
					bCount++;
				else
					bCount = 0;

				if (board[y + x][x] == WHITE_DOL)
					wCount++;
				else
					wCount = 0;

				if (board[Y_COUNT - 1 - x + y][x] == BLACK_DOL)
					b2Cnt++;
				else
					b2Cnt = 0;

				if (board[Y_COUNT - 1 - x + y][x] == WHITE_DOL)
					w2Cnt++;
				else
					w2Cnt = 0;

				if (bCount >= 5 || b2Cnt >= 5) return BLACK_DOL;
				else if (wCount >= 5 || w2Cnt >= 5) return WHITE_DOL;
			}
		}
	}

	return 0;
}

void Reset(HWND hWnd)
{
	for (int x = 0; x < X_COUNT; x++)
	{
		for (int y = 0, xCount = 0; y < Y_COUNT; y++)
			board[y][x] = 0;
	}

	pieceCount = 0;
	turn = true;

	InvalidateRect(hWnd, nullptr, true);
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
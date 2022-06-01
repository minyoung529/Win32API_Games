#include "GameScene.h"
#include "resource.h"
#include "ObjectManager.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	background = LoadBitmap(engine->GetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP1));

	backgroundRect.left = MARGIN_COLUMN + GAP;
	backgroundRect.right = backgroundRect.left + BOARDSIZE_X;
	backgroundRect.top = MARGIN_ROW + GAP;
	backgroundRect.bottom = backgroundRect.top + BOARDSIZE_Y;

	previewRect.left = MARGIN_COLUMN + BOARDSIZE_X + RATIO;
	previewRect.right = previewRect.left + RATIO * 4;
	previewRect.top = MARGIN_ROW;
	previewRect.bottom = previewRect.top + RATIO * 4;

	gameStart = false;
	memset(&inputState, 0, sizeof(InputState));

	ObjectManager::GetInstance()->Init();
}

void GameScene::Update(float deltaTime)
{
	if (ObjectManager::GetInstance()->GetGameOver())
	{
		if (MessageBox(engine->GetWndHandle(), TEXT("GameOver!"), TEXT("Game"), MB_OK))
		{
			SendMessage(engine->GetWndHandle(), WM_DESTROY, 0, 0);
		}

		return;
	}

	engine->Input.KeyCheck(VK_RETURN, inputState.keyReturn);

	if (inputState.keyReturn == KEY_UP)
	{
		if (!gameStart)
		{
			gameStart = true;
			ObjectManager::GetInstance()->CreatePrevBlock();
			ObjectManager::GetInstance()->CreateGameBlock();
		}
	}

	ObjectManager::GetInstance()->Update(deltaTime);
}

void GameScene::Render(HDC hdc, float deltaTime)
{
	HDC memDC = CreateCompatibleDC(hdc);
	HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, background);

	BitBlt(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, memDC, 0, 0, SRCCOPY);
	SelectObject(memDC, oldBitmap);
	DeleteDC(memDC);

	HBRUSH myBrush = CreateSolidBrush(RGB(22, 23, 67));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

	Rectangle(hdc, backgroundRect.left, backgroundRect.top, backgroundRect.right, backgroundRect.bottom);
	Rectangle(hdc, previewRect.left, previewRect.top, previewRect.right, previewRect.bottom);

	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);

	WCHAR str[128];
	wsprintf(str, TEXT("SCORE : %d"), ObjectManager::GetInstance()->GetScore());
	TextOut(hdc, 90, 70, str, lstrlen(str));

	if (gameStart)
	{
		ObjectManager::GetInstance()->Render(hdc);
	}
	else
	{
		TextOut(hdc, 240, 300, TEXT("ENTER키를 누르면 시작합니다!"), 18);
	}

}

void GameScene::Release()
{
	DeleteObject(background);
	ObjectManager::GetInstance()->Release();
}

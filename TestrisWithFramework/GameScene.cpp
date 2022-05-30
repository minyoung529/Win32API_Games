#include "GameScene.h"
#include "resource.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	piece = new Piece(POINT{ 10,10 }, PIECE_COLOR::ORNAGE);
	block = new Block(TETRIS_TYPE::Z);

	background = LoadBitmap(engine->GetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP1));

	backgroundRect.left = MARGIN_COLUMN + GAP;
	backgroundRect.right = backgroundRect.left + BOARDSIZE_X;
	backgroundRect.top = MARGIN_ROW + GAP;
	backgroundRect.bottom = backgroundRect.top + BOARDSIZE_Y;

	previewRect.left = MARGIN_COLUMN + BOARDSIZE_X + RATIO;
	previewRect.right = previewRect.left + RATIO * 4;
	previewRect.top = MARGIN_ROW;
	previewRect.bottom = previewRect.top + RATIO * 4;

}

void GameScene::Update(float deltaTime)
{
	block->Update(deltaTime);
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

	if (piece)
		piece->Render(hdc);

	if (block)
		block->Render(hdc);
}

void GameScene::Release()
{
}

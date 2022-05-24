#include "Piece.h"
#include "BasisSystem.h"

Piece::Piece()
	: Object(TAG::PIECE)
	, position{}
	, color(PIECE_COLOR::NONE)
{
}

Piece::Piece(POINT pos, PIECE_COLOR color)
	: Object(TAG::PIECE)
	, position(pos)
	, color(color)
{
}

Piece::~Piece()
{
}

void Piece::Init()
{
}

void Piece::Update(float deltaTime)
{
}

void Piece::Render(HDC hdc)
{
	HDC memDC;
	HBITMAP myBitmap, oldBitmap;

	memDC = CreateCompatibleDC(hdc);
	myBitmap = LoadBitmap(engine->GetInstanceHandle(), MAKEINTRESOURCE(color));
	oldBitmap = (HBITMAP)SelectObject(memDC, myBitmap);

	BitBlt(hdc, position.x * RATIO + GAP, position.y * RATIO + GAP, RATIO - GAP, RATIO - GAP,
		memDC, 0, 0, SRCCOPY);

	SelectObject(memDC, oldBitmap);
	DeleteObject(myBitmap);
	DeleteDC(memDC);
}

void Piece::Release()
{
}

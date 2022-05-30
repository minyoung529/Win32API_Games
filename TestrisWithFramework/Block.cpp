#include "Block.h"

Block::Block()
	: Object(TAG::BLOCK)
	, center{}
	, color(PIECE_COLOR::NONE)
	, type(TETRIS_TYPE::I)
	, startTime(GetTickCount64())
	, delayTime(DELAYTIME)
{
}

Block::Block(TETRIS_TYPE type)
	: Object(TAG::BLOCK)
	, center{}
	, color(PIECE_COLOR::NONE)
	, type(type)
	, startTime(GetTickCount64())
	, delayTime(DELAYTIME)
{
	center.x = 10;
	center.y = 2;

	InitBlock(type);
	memset(&inputState, 0, sizeof(InputState));
}

Block::~Block()
{
}

void Block::Init()
{
}

void Block::Update(float deltaTime)
{
	int currentTime = GetTickCount64();

	if (currentTime - startTime >= delayTime)
	{
		startTime = currentTime;
		++center.y;
	}

	engine->Input.KeyCheck(VK_UP, inputState.keyUp);

	if (inputState.keyUp == KEY_PUSH)
	{
		if (type != TETRIS_TYPE::O)
			RightRotateBlock();
	}
}

void Block::Render(HDC hdc)
{
	HDC memDC = CreateCompatibleDC(hdc);
	HBITMAP myBitmap = LoadBitmap(engine->GetInstanceHandle(), MAKEINTRESOURCE(color));
	HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, myBitmap);

	for (UINT i = 0; i < POINTNUM; i++)
	{
		BitBlt(
			hdc,
			GetGlobalX(point[i].x) * RATIO + GAP,
			GetGlobalY(point[i].y) * RATIO + GAP,
			RATIO - GAP, RATIO - GAP, memDC, 0, 0, SRCCOPY);
	}

	SelectObject(memDC, oldBitmap);
	DeleteObject(myBitmap);
	DeleteDC(memDC);
}

void Block::Release()
{
}

int Block::GetGlobalX(const int x) const
{
	return center.x + x;
}

int Block::GetGlobalY(const int y) const
{
	return center.y + y;
}

void Block::InitBlock(TETRIS_TYPE type)
{
	switch (type)
	{
	case TETRIS_TYPE::I:
		point[0].x = 0; point[0].y = -1;
		point[1].x = 0; point[1].y = 1;
		point[2].x = 0; point[2].y = 2;
		point[3].x = 0; point[3].y = 0;

		color = PIECE_COLOR::BLUE;
		break;

	case TETRIS_TYPE::O:
		point[0].x = 0; point[0].y = 1;
		point[1].x = -1; point[1].y = 1;
		point[2].x = -1; point[2].y = 0;
		point[3].x = 0; point[3].y = 0;

		color = PIECE_COLOR::PURPLE;
		break;

	case TETRIS_TYPE::Z:
		point[0].x = 1; point[0].y = -1;
		point[1].x = 1; point[1].y = 0;
		point[2].x = 0; point[2].y = 1;
		point[3].x = 0; point[3].y = 0;

		color = PIECE_COLOR::GRAY;
		break;

	case TETRIS_TYPE::S:
		point[0].x = 0; point[0].y = -1;
		point[1].x = 1; point[1].y = 0;
		point[2].x = 1; point[2].y = 1;
		point[3].x = 0; point[3].y = 0;

		color = PIECE_COLOR::RED;
		break;

	case TETRIS_TYPE::J:
		point[0].x = -1; point[0].y = -1;
		point[1].x = -1; point[1].y = 0;
		point[2].x = 1; point[2].y = 0;
		point[3].x = 0; point[3].y = 0;

		color = PIECE_COLOR::ORNAGE;
		break;

	case TETRIS_TYPE::L:
		point[0].x = 1; point[0].y = -1;
		point[1].x = -1; point[1].y = 0;
		point[2].x = 1; point[2].y = 0;
		point[3].x = 0; point[3].y = 0;

		color = PIECE_COLOR::GUIDE;
		break;

	case TETRIS_TYPE::T:
		point[0].x = -1; point[0].y = 0;
		point[1].x = 1; point[1].y = 0;
		point[2].x = 0; point[2].y = 1;
		point[3].x = 0; point[3].y = 0;

		color = PIECE_COLOR::GREEN;
		break;

	default:
		break;
	}
}

void Block::RightRotatePiece(LONG& x, LONG& y)
{
	LONG temp = x;
	x = -y;
	y = temp;
}

void Block::RightRotateBlock()
{
	for (UINT i = 0; i < POINTNUM; ++i)
	{
		RightRotatePiece(point[i].x, point[i].y);
	}
}

void Block::LeftRotatePiece(LONG& x, LONG& y)
{
	LONG temp = x;
	x = y;
	y = -temp;

}

void Block::LeftRotateBlock()
{
	for (UINT i = 0; i < POINTNUM; ++i)
	{
		LeftRotatePiece(point[i].x, point[i].y);
	}
}
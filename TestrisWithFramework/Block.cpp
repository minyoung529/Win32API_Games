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
}

Block::~Block()
{
}

void Block::Init()
{
}

void Block::Update(float deltaTime)
{
}

void Block::Render(HDC hdc)
{
}

void Block::Release()
{
}

int Block::GetGlobalX(const int x) const
{
	return 0;
}

int Block::GetGlobalY(const int y) const
{
	return 0;
}

void Block::CreateBlock(TETRIS_TYPE type)
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
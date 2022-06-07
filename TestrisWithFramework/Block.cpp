#include "Block.h"
#include "ObjectManager.h"

Block::Block()
	: Object(TAG::BLOCK)
	, center{}
	, color(PIECE_COLOR::NONE)
	, type(TETRIS_TYPE::I)
	, startTime(GetTickCount64())
	, delayTime(DELAYTIME)
	, state(BLOCK_STATE::FROZEN)
{
}

Block::Block(TETRIS_TYPE type, BLOCK_STATE state)
	: Object(TAG::BLOCK)
	, center{}
	, color(PIECE_COLOR::NONE)
	, type(type)
	, state(state)
	, startTime(GetTickCount64())
	, delayTime(DELAYTIME)
{
	if (state == BLOCK_STATE::HANDLENOW)
	{
		center.x = HANDLE_POS_X;
		center.y = HANDLE_POS_Y;
	}

	else if (state == BLOCK_STATE::PREVIEW)
	{
		center.x = PREVIEW_POS_X;
		center.y = PREVIEW_POS_Y;
	}

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
	if (state == BLOCK_STATE::HANDLENOW)
	{
		int currentTime = GetTickCount64();

		if (currentTime - startTime >= delayTime)
		{
			POINT temp{ center.x, center.y + 1 };
			startTime = currentTime;

			if (!ReachTheGround(center) && !ObjectManager::GetInstance()->CheckOverlapWithPiece(temp, point))
			{
				++center.y;
			}
		}

		engine->Input.KeyCheck(VK_UP, inputState.keyUp);
		engine->Input.KeyCheck(VK_DOWN, inputState.keyDown);
		engine->Input.KeyCheck(VK_LEFT, inputState.keyLeft);
		engine->Input.KeyCheck(VK_RIGHT, inputState.keyRight);
		engine->Input.KeyCheck(VK_SPACE, inputState.keySpace);

		// 윗 키 (회전)
		if (inputState.keyUp == KEY_PUSH)
		{
			if (type != TETRIS_TYPE::O)
			{
				POINT _point[POINTNUM];
				memcpy(_point, point, sizeof(_point));

				if (!ReachTheGround(center)
					&& !ObjectManager::GetInstance()->CheckOverlapWithPiece(center, point))
				{
					RightRotateBlock();
				}
			}
		}

		// 아래 키
		if (inputState.keyDown == KEY_PUSH)
		{
			POINT temp{ center.x, center.y + 1 };

			if (!ReachTheGround(center) && !ObjectManager::GetInstance()->CheckOverlapWithPiece(temp, point))
			{
				++center.y;
			}
		}

		// 왼
		if (inputState.keyLeft == KEY_PUSH)
		{
			POINT temp{ center.x - 1, center.y };

			if (!CheckOutOfRange(temp, point) && !ObjectManager::GetInstance()->CheckOverlapWithPiece(temp, point))
			{
				--center.x;
			}
		}

		// 오
		if (inputState.keyRight == KEY_PUSH)
		{
			POINT temp{ center.x + 1, center.y };

			if (!CheckOutOfRange(temp, point) && !ObjectManager::GetInstance()->CheckOverlapWithPiece(temp, point))
			{
				++center.x;
			}
		}

		// 한번에 내려가기
		if (inputState.keySpace == KEY_UP)
		{
			POINT temp{ center.x , center.y + 1 };

			while (!ReachTheGround(center) && !ObjectManager::GetInstance()->CheckOverlapWithPiece(temp, point))
			{
				++center.y;
				temp.y = center.y + 1;
			}
		}
	}

	POINT temp{ center.x , center.y + 1 };

	if (ReachTheGround(center) ||  ObjectManager::GetInstance()->CheckOverlapWithPiece(temp, point))
	{
		ULONGLONG currentTime = GetTickCount64();
		if (currentTime - startTime >= 500)
		{
			startTime = currentTime;
			RemoveBlockMakePiece();
		}
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

	while (CheckOutOfLeft(center, point))
	{
		++center.x;
	}

	while (CheckOutOfRight(center, point))
	{
		--center.x;
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

bool Block::IsRightRotateBlock(POINT pt[])
{
	for (UINT i = 0; i < POINTNUM; ++i)
	{
		RightRotatePiece(pt[i].x, pt[i].y);
	}

	return false;
}

bool Block::CheckOutOfLeft(const POINT center, const POINT pt[]) const
{
	for (UINT i = 0; i < POINTNUM; ++i)
	{
		if (center.x + pt[i].x < (MARGIN_COLUMN / RATIO))
			return true;
	}
	return false;
}

bool Block::CheckOutOfRight(const POINT center, const POINT pt[]) const
{
	for (UINT i = 0; i < POINTNUM; ++i)
	{
		if (center.x + pt[i].x >= ((MARGIN_COLUMN + BOARDSIZE_X) / RATIO))
			return true;
	}

	return false;
}

bool Block::ReachTheGround(const POINT center) const
{
	for (UINT i = 0; i < POINTNUM; ++i)
	{
		if (center.y + point[i].y >= (MARGIN_ROW + BOARDSIZE_Y) / RATIO - 1)
			return true;
	}
	return false;
}

bool Block::CheckOutOfRange(const POINT center, const POINT pt[]) const
{
	for (UINT i = 0; i < POINTNUM; ++i)
	{
		if (center.x + pt[i].x < (MARGIN_COLUMN / RATIO) ||
			center.x + pt[i].x >((MARGIN_COLUMN + BOARDSIZE_X) / RATIO) - 1)
		{
			return true;
		}
	}

	return false;
}

void Block::RemoveBlockMakePiece()
{
	state = BLOCK_STATE::FROZEN;

	for (UINT i = 0; i < POINTNUM; ++i)
	{
		ObjectManager::GetInstance()->
			RegisterObject(new Piece({ GetGlobalX(point[i].x), GetGlobalY(point[i].y) }, color));
	}

	ObjectManager::GetInstance()->RemoveObject(this->GetId());

	vector<Object*> gameObjects = ObjectManager::GetInstance()->GetGameObjectList();

	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i]->GetTag() == TAG::BLOCK)
		{
			// point => dymanic
			Block* block = dynamic_cast<Block*>(gameObjects[i]);
			if (block->GetState() == BLOCK_STATE::PREVIEW)
			{
				POINT pos{ HANDLE_POS_X, HANDLE_POS_Y };

				if (ObjectManager::GetInstance()->CheckOverlapWithPiece(pos, point))
				{
					ObjectManager::GetInstance()->SetGameOver(true);
				}

				block->SetState(BLOCK_STATE::HANDLENOW);
				block->SetCenter(pos);
			}
		}
	}

	ObjectManager::GetInstance()->CreatePrevBlock();
}

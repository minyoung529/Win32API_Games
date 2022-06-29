#include "PixelCollision.h"

PixelCollision::PixelCollision()
{
	stage = STAGE::STAGE1;
	player = nullptr;
	currentMemDC = nullptr;
	currentMemDC = nullptr;
}

PixelCollision::~PixelCollision()
{
	if (currentMemDC)
	{
		SelectObject(currentMemDC, oldBitmap);
		DeleteDC(currentMemDC);
	}
}

void PixelCollision::Init()
{
	imagePixels[STAGE::STAGE1].Load(TEXT("Data/BackGround/background_pixel.bmp"));
	imagePixels[STAGE::STAGE2].Load(TEXT("Data/BackGround/background2_pixel.bmp"));
	imagePixels[STAGE::STAGE3].Load(TEXT("Data/BackGround/background2_pixel.bmp"));
}

void PixelCollision::Update(float deltaTime)
{
	// 주인공 픽셀 충돌
	PlayerPixelCollision();

	// 몬스터들 픽셀 충돌
	MonstersPixelCollision();
}

void PixelCollision::Render(HDC hdc)
{
}

void PixelCollision::Release()
{
	imagePixels[STAGE::STAGE1].Release();
	imagePixels[STAGE::STAGE2].Release();
	imagePixels[STAGE::STAGE3].Release();
}

void PixelCollision::SetPlayer(Player* player)
{
	this->player = player;
}

void PixelCollision::SetStage(STAGE stage)
{
	if (stage < STAGE1 || stage >= STAGE_COUNT) return;

	currentPixel = &imagePixels[stage];

	if (currentMemDC)
	{
		SelectObject(currentMemDC, oldBitmap);
		DeleteDC(currentMemDC);
	}

	HDC hdc = GetDC(engine->GetWndHandle());
	currentMemDC = CreateCompatibleDC(hdc);

	oldBitmap = (HBITMAP)SelectObject(currentMemDC, currentPixel->GetBitmapHandle());
}

void PixelCollision::PlayerPixelCollision()
{
	int startY = player->GetPos().y;
	int startX = player->GetPos().x;

	for (int y = startY; y < startY + player->GetSize().height; ++y)
	{
		for (int x = startX; x <= startX + player->GetSize().width; ++x)
		{
			COLORREF color = GetPixel(currentMemDC, x, y);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 0 && g == 255 && b == 255))
			{
				if (!player->GetIsOnGround() && !player->IsJumping())
				{
					player->SetIsOnGround(true);
					break;
				}
			}
			else
			{
				if (!(player->IsJumping() || player->IsFalling()))
				{
					player->SetIsOnGround(false);
				}
			}
		}
	}

	for (int y = startY; y < startY + player->GetSize().height / 2; ++y)
	{
		int x = player->IsLeft() ? startX : startX + player->GetSize().width;

		COLORREF color = GetPixel(currentMemDC, x, y);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 0 && g == 255 && b == 255))
		{
			if (player->IsLeft())
				player->SetCanMoveLeft(false);
			else
				player->SetCanMoveRight(false);
		}
		else if ((r == 255 && g == 0 && b == 255))
		{
			break;
		}
		else
		{
			player->SetCanMoveLeft(true);
			player->SetCanMoveRight(true);
		}
	}
}

void PixelCollision::MonstersPixelCollision()
{
	for (size_t i = 0; i < monsters->size(); ++i)
	{
		Monster* monster = monsters->at(i);

		int startY = monster->GetPos().y + monster->GetSize().height - 5;

		for (int y = startY; y <= monster->GetPos().y + monster->GetSize().height; ++y)
		{
			COLORREF color = GetPixel(currentMemDC, monster->GetPos().x, y);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 0 && g == 255 && b == 255))
			{
				monster->SetIsOnGround(true);
			}
			else
			{
				monster->SetIsOnGround(false);
			}
		}

		if (monster->GetState() == MONSTER_STATE::LEFT_MOVE || monster->GetState() == MONSTER_STATE::RIGHT_MOVE)
		{
			int y = monster->GetPos().y;
			int x = monster->IsLeft() ? monster->GetPos().x : monster->GetPos().x + monster->GetSize().width;

			COLORREF color = GetPixel(currentMemDC, x, y);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 0 && g == 255 && b == 255))
			{
				if (monster->IsLeft())
					monster->SetCanMoveLeft(false);
				else
					monster->SetCanMoveRight(false);
			}
			else
			{
				monster->SetCanMoveLeft(true);
				monster->SetCanMoveRight(true);
			}
		}
	}
}
#include "Background.h"

Background::Background()
{
	stage = STAGE1;
	player = nullptr;
	currentBG = nullptr;

	memset(loopInfos, 0, sizeof(loopInfos));

	loopInfos[0].speed = 2;
	loopInfos[1].speed = 1;
	loopInfos[2].speed = 0;
	loopInfos[3].speed = 1;
}

Background::~Background()
{
}

void Background::Init()
{
	imageBackgrounds[STAGE1].Load(TEXT("Data/BackGround/background.bmp"));
	imageBackgrounds[STAGE2].Load(TEXT("Data/BackGround/background2.bmp"));
	imageBackgrounds[STAGE3].Load(TEXT("Data/BackGround/background3.bmp"));

	imageLoopBackground[LOOPBG1].Load(TEXT("Data/BackGround/back1.bmp"));
	imageLoopBackground[LOOPBG2].Load(TEXT("Data/BackGround/back2.bmp"));
	imageLoopBackground[LOOPBG3].Load(TEXT("Data/BackGround/back3.bmp"));
	imageLoopBackground[LOOPBG4].Load(TEXT("Data/BackGround/back4.bmp"));

}

void Background::Update(float deltaTime)
{
	if (engine->cameraObject.CheckCameraX() && player)
	{
		if (player->IsMovingRight())
		{
			for (int i = LOOPBG1; i < LOOP_COUNT; ++i)
				loopInfos[i].posX += loopInfos[i].speed;
		}

		if (player->IsMovingLeft())
		{
			for (int i = LOOPBG1; i < LOOP_COUNT; ++i)
				loopInfos[i].posX -= loopInfos[i].speed;
		}
	}
}

void Background::Render(HDC hdc, float deltaTime)
{
	RECT rect = { 0,0,SCREEN_WIDTH * 2,SCREEN_HEIGHT };

	for (int i = LOOP_COUNT - 1; i >= LOOPBG1; --i)
	{
		imageLoopBackground[i].DrawLoopRender(hdc, rect, loopInfos[i].posX, 0);
	}

	if (currentBG)
		currentBG->DrawBitmap(hdc, 0, 0, 0, 0);
}

void Background::Release()
{
	imageBackgrounds[STAGE1].Release();
	imageBackgrounds[STAGE2].Release();
	imageBackgrounds[STAGE3].Release();

	for (int i = LOOPBG1; i < LOOP_COUNT; ++i)
	{
		imageLoopBackground[i].Release();
	}

}

void Background::SetStage(STAGE stage)
{
	if (stage < 0 || stage >= STAGE_COUNT) return;

	currentBG = &imageBackgrounds[stage];
}

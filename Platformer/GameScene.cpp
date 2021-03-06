#include "GameScene.h"
#include "MonsterManager.h"
#include "BasisStd.h"

GameScene::GameScene()
{
	player = nullptr;
	background = nullptr;
	pixelCollision = nullptr;

	stage = STAGE1;
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	player = new Player(FPOINT{ 200,200 }, OBJSIZE{ 96,96 }, 100.0f);

	MonsterManager::GetSingleton()->ClearMonster();
	MonsterManager::GetSingleton()->RegisterMonster(MONSTER_TYPE::KING_PIG, FPOINT{ 600,450 });
	MonsterManager::GetSingleton()->RegisterMonster(MONSTER_TYPE::KING_PIG, FPOINT{ 1218,447 });
	MonsterManager::GetSingleton()->Init();
	MonsterManager::GetSingleton()->SetPlayer(player);

	if (player)
		player->Init();

	background = new Background();

	if (background)
	{
		background->Init();
		background->SetStage(stage);
		background->SetPlayer(player);
	}

	pixelCollision = new PixelCollision();
	if (pixelCollision)
	{
		pixelCollision->Init();
		pixelCollision->SetStage(stage);
		pixelCollision->SetPlayer(player);
		pixelCollision->SetMonsters(&MonsterManager::GetSingleton()->GetMonsters());
	}

	engine->cameraObject.Init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH * 2, SCREEN_HEIGHT);
}

void GameScene::Update(float deltaTime)
{
	if (player)
		player->Update(deltaTime);

	MonsterManager::GetSingleton()->Update(deltaTime);

	if (background)
		background->Update(deltaTime);

	if (pixelCollision)
		pixelCollision->Update(deltaTime);


	if (engine->cameraObject.GetIsShaking())
		engine->cameraObject.CameraShake();
	else
		engine->cameraObject.SetPos(player->GetPos().x, player->GetPos().y);
}

void GameScene::Render(HDC hdc, float dt)
{
	int width = SCREEN_WIDTH * 2;
	int height = SCREEN_HEIGHT;
	HDC hMemDC = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);

	if (background)
		background->Render(hMemDC, dt);

	if (pixelCollision)
		pixelCollision->Render(hMemDC);

	if (player)
		player->Render(hMemDC, dt);

	MonsterManager::GetSingleton()->Render(hMemDC);

	GdiTransparentBlt(hdc, 0 + engine->cameraObject.GetShakeNumber(), 0, SCREEN_WIDTH, SCREEN_HEIGHT,
		hMemDC, engine->cameraObject.GetLeft(), engine->cameraObject.GetTop(),
		engine->cameraObject.GetWidth(), engine->cameraObject.GetHeight(), RGB(255, 0, 255));

	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hBitmap);
	DeleteDC(hMemDC);
}

void GameScene::Release()
{
	if (player)
		player->Release();

	MonsterManager::GetSingleton()->Release();

	if (background)
		background->Release();

	if (pixelCollision)
		pixelCollision->Release();

	SAFE_DELETE(player);
	SAFE_DELETE(background);
	SAFE_DELETE(pixelCollision);
}
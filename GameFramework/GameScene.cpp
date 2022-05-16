#include "GameScene.h"

GameScene::GameScene()
{
	player = new Player(FPOINT{ 200,550 }, OBJECTSIZE{}, 200);
	background = new Background(FPOINT{ 0,0 }, OBJECTSIZE{});
}


GameScene::~GameScene()
{
	if (player) delete player;
	if (background) delete background;
}

void GameScene::Init()
{
	if (background)  background->Init();
	if (player) player->Init();

	EnemyManager::Instance()->Init();
}

void GameScene::Update(float deltaTime)
{
	if (background)  background->Update(deltaTime);
	if (player) player->Update(deltaTime);

	EnemyManager::Instance()->Update(deltaTime);
	EnemyManager::Instance()->SetTargetPos(player->GetCenter());
}

void GameScene::Render(HDC hdc, float deltaTime)
{
	if (background) background->Render(hdc, deltaTime);
	if (player) player->Render(hdc, deltaTime);

	EnemyManager::Instance()->Render(hdc, deltaTime);
}

void GameScene::Release()
{
	if (player) player->Release();
	if (background) background->Release();

	EnemyManager::Instance()->Release();
}
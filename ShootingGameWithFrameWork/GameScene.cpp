#include "GameScene.h"
#include "BasisSystem.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	player = new Player(FPOINT{ 200,550 }, OBJECTSIZE{}, 200, 0.5f);
	background = new Background(FPOINT{ 0,0 }, OBJECTSIZE{});

	if (background)  background->Init();
	if (player) player->Init();

	EnemyManager::Instance()->Init();
}

void GameScene::Update(float deltaTime)
{
	if (background)  background->Update(deltaTime);
	if (player)
	{
		player->Update(deltaTime);
		EnemyManager::Instance()->SetTargetPos(player->GetCenter());
		if (EnemyManager::Instance()->IsBulletCollision(player->GetRect()))
		{
			player->AddHP(-1.f);

			if (player->GetHP() < 0.f && engine->mSceneManager)
			{
				engine->mSceneManager->ReserveChangeScene("EndScene");
			}
		}
	}

	EnemyManager::Instance()->Update(deltaTime);
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

	if (player) delete player;
	if (background) delete background;
}
#include "GameScene.h"
#include "BasisStd.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{

}

void GameScene::Init()
{
    player = new Player(FPOINT{ 200,200 }, OBJSIZE{96,96}, 100.0f);

    if (player)
        player->Init();
}


void GameScene::Update(float dt)
{
    if (player)
    {
        player->Update(dt);
    }
}

void GameScene::Render(HDC hdc, float dt)
{
    if (player)
        player->Render(hdc, dt);
}

void GameScene::Release()
{
    if (player)
        player->Release();
}
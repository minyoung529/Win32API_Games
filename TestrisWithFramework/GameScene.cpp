#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	piece = new Piece(POINT{ 10,10 }, PIECE_COLOR::ORNAGE);
}

void GameScene::Update(float deltaTime)
{
}

void GameScene::Render(HDC hdc, float deltaTime)
{
	if (piece)
	{
		piece->Render(hdc);
	}
}

void GameScene::Release()
{
}

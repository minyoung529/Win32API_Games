#include "pch.h"
#include "Scene_Start.h"
#include "Object.h"
#include "Player.h"
#include "Monster.h"
#include "Core.h"
#include "Image.h"
#include "PathManager.h"

Scene_Start::Scene_Start()
{
}

Scene_Start::~Scene_Start()
{

}

void Scene_Start::Enter()
{
	Vector2 vResolution = Core::GetInst()->GetResolution();

	// Object »ý¼º
	Object* pObj = new Player;
	pObj->SetPos(Vector2(640, 400));
	pObj->SetScale(Vector2(100, 100));

	AddObject(pObj, GROUP_TYPE::PLAYER);

	int iMonster = 5;
	float term = (vResolution.x - (75.f * 2)) / (float)(iMonster - 1);

	for (int i = 0; i < iMonster; i++)
	{
		Monster* monster = new Monster;
		monster->SetPos(Vector2(75.f + term * (float)i, 50.f));
		monster->SetScale(Vector2(50, 50));
		monster->SetCenterPosition(monster->GetPos());

		AddObject(monster, GROUP_TYPE::MONSTER);
	}
}

void Scene_Start::Exit()
{

}
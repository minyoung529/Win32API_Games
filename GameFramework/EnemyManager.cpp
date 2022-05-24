#include "EnemyManager.h"

EnemyManager* EnemyManager::enemyManager = nullptr;

EnemyManager::EnemyManager()
	: level(1)
	, scale(1.0f)
	, moveSpeed(50.0f)
{
	srand((unsigned int)time(NULL));
}

EnemyManager::~EnemyManager()
{
	for (UINT i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Release();
		delete enemies[i];
		enemies.erase(enemies.begin() + i);
	}

	enemies.clear();
}

void EnemyManager::Init()
{
	level = 1;
	moveSpeed = 50.f;
	enemies.reserve(100);
	CreateEnemy(level);
}

void EnemyManager::Update(float deltaTime)
{
	if (enemies.size() == 0)
	{
		CreateEnemy(++level);
	}

	for (UINT i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->GetCollision())
		{
			enemies[i]->Release();
			delete enemies[i];
			enemies.erase(enemies.begin() + i);
		}
		else
		{
			enemies[i]->Update(deltaTime);

		}
	}
}

void EnemyManager::Render(HDC hdc, float deltaTime)
{
	for (UINT i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Render(hdc, deltaTime);
	}
}

void EnemyManager::Release()
{
	for (UINT i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Release();
	}
}

bool EnemyManager::IsCollision(RECT* rect, RECT* targetRect)
{
	bool collision = false;

	for (UINT i = 0; i < enemies.size(); i++)
	{
		if (IntersectRect(rect, targetRect, enemies[i]->GetRect()))
		{
			collision = true;
			enemies[i]->SetCollision(true);
		}
	}

	return collision;
}

bool EnemyManager::IsBulletCollision(RECT* targetRect)
{
	bool isCollision = false;

	for (UINT i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->IsBulletCollision(targetRect))
		{
			isCollision = true;
		}
	}

	return isCollision;
}

void EnemyManager::CreateEnemy(int level)
{
	BULLET_TYPE bulletType = BULLET_TYPE::NORMAL;

	if (level % 2 == 0)
	{
		bulletType = BULLET_TYPE::FOLLOW;
	}
	else
	{
		bulletType = BULLET_TYPE::BARRAGE;
	}

	for (int i = 1; i <= 10; i++)
	{
		Enemy* enemy = new Enemy(FPOINT{ rand() % 350 + 40.f, rand() % 200 + 50.f },
			OBJECTSIZE{}, scale / level, moveSpeed * level, bulletType);

		if (enemy) enemy->Init();

		enemies.push_back(enemy);
	}
}

void EnemyManager::SetTargetPos(FPOINT pos)
{
	for (UINT i = 0; i < enemies.size(); i++)
	{
		enemies[i]->SetTargetPos(pos);
	}
}
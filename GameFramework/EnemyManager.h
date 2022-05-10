#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include "Enemy.h"

class EnemyManager
{
private:
	static EnemyManager* enemyManager;

public:
	static EnemyManager* Instance()
	{
		if (enemyManager == nullptr)
		{
			enemyManager = new EnemyManager;
		}

		return enemyManager;
	}

	static void DeleteInstance()
	{
		if (enemyManager != nullptr)
		{
			delete enemyManager;
			enemyManager = nullptr;
		}
	}

private:
	EnemyManager();
	~EnemyManager();

public:
	void Init();
	void Update(float deltaTime);
	void Render(HDC hdc, float deltaTime);
	void Release();

public:
	bool IsCollision(RECT* rect, RECT* targetRect);
	void CreateEnemy(int level);

private:
	vector<Enemy*>	enemies;
	int				level;
	float			moveSpeed;
	float			scale;
};

#endif
#include "Enemy.h"

Enemy::Enemy()
	:Object(FPOINT{}, OBJECTSIZE{}, 1.f)
	, speed(50.f)
	, collider{}
	, isCollision(false)
	, regenTime(0.3f)
	, maxRegen(3.f)
	, accTime(0.f)
	, bulletType(BULLET_TYPE::NORMAL)
{
	scale = 1.f;
}

Enemy::Enemy(FPOINT pos, OBJECTSIZE size, float scale, float speed)
	:Object(pos, size, scale)
	, speed(speed)
	, collider{}
	, isCollision(false)
	, regenTime(0.3f)
	, maxRegen(3.f)
	, accTime(0.f)
	, bulletType(BULLET_TYPE::NORMAL)
{
	this->scale = scale;
}

Enemy::Enemy(FPOINT pos, OBJECTSIZE size, float scale, float speed, BULLET_TYPE type)
	:Object(pos, size, scale)
	, speed(speed)
	, collider{}
	, isCollision(false)
	, regenTime(0.3f)
	, maxRegen(3.f)
	, accTime(0.f)
	, bulletType(type)

{
}


Enemy::~Enemy()
{
}

void Enemy::Init()
{
	enemyImage.Load(TEXT("Data/enemy.bmp"));
	size.width = enemyImage.GetBitmapInfo().bmWidth;
	size.height = enemyImage.GetBitmapInfo().bmHeight;

	UpdateCollider();

	if (rand() % 2 == 0)
		speed *= -1.f;
}

void Enemy::Update(float deltaTime)
{
	UpdateCollider();
	Move(deltaTime);

	accTime += deltaTime;
	if (accTime >= regenTime)
	{
		switch (bulletType)
		{
		case BULLET_TYPE::NORMAL:
			break;

		case BULLET_TYPE::FOLLOW:
		{
			if (bullets.size() == 0)
			{
				EnemyBullet* newBullet =
					new EnemyBullet(FPOINT{ pos.x, pos.y }, OBJECTSIZE{}, 200.f, targetPos);

				if (newBullet)
				{
					newBullet->Init();
					bullets.push_back(newBullet);
				}
				regenTime = rand() % (int)maxRegen + 1;
				accTime = 0.f;
			}
		}break;

		case BULLET_TYPE::BARRAGE:
		{
			for (UINT i = 0; i < 20; i++)
			{
				EnemyBullet* newBullet =
					new EnemyBullet(FPOINT{ pos.x, pos.y }, OBJECTSIZE{}, 200.f, (float)2 * PI / 20 * i);

				if (newBullet)
				{
					newBullet->Init();
					bullets.push_back(newBullet);
				}
			}

			regenTime = rand() % (int)maxRegen + 1;
			accTime = 0.f;
		}break;
		}
	}

	for (UINT i = 0; i < bullets.size(); i++)
	{
		bullets[i]->Update(deltaTime);

		if (!bullets[i]->IsValid())
		{
			bullets[i]->Release();
			delete bullets[i];
			bullets.erase(bullets.begin() + i);
		}
	}
}

void Enemy::Render(HDC hdc, float deltaTime)
{
	enemyImage.DrawBitmap(hdc, (int)pos.x, (int)pos.y,
		(int)(size.width * scale), (int)(size.height * scale));

	SelectObject(hdc, GetStockObject(NULL_BRUSH));
	Rectangle(hdc, collider.left, collider.top,
		collider.right, collider.bottom);

	for (UINT i = 0; i < bullets.size(); i++)
	{
		bullets[i]->Render(hdc, deltaTime);
	}
}

void Enemy::Release()
{
	for (UINT i = 0; i < bullets.size(); i++)
	{
		bullets[i]->Release();
		delete bullets[i];
		bullets.erase(bullets.begin() + i);
	}

	enemyImage.Release();
}

void Enemy::UpdateCollider()
{
	collider.left = pos.x;
	collider.right = pos.x + (int)(size.width * scale);

	collider.top = pos.y;
	collider.bottom = pos.y + (int)(size.height * scale);
}

bool Enemy::GetCollision()
{
	return isCollision;
}

void Enemy::SetCollision(bool isCollision)
{
	this->isCollision = isCollision;
}

RECT* Enemy::GetRect()
{
	return &collider;
}

bool Enemy::IsBulletCollision(RECT* targetRect)
{
	bool isCollision = false;

	for (UINT i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->IsCollision(targetRect))
		{
			bullets[i]->Release();
			delete bullets[i];
			bullets.erase(bullets.begin() + i);
			isCollision = true;
		}
	}

	return isCollision;
}

void Enemy::Move(float deltaTime)
{
	pos.x += speed * deltaTime;

	RECT rt;
	GetClientRect(engine->GetWndHandle(), &rt);
	rt.right -= (collider.right - collider.left);

	if (!PtInRect(&rt, POINT{ (int)pos.x, (int)pos.y }))
	{
		if (pos.x <= rt.left)
			pos.x += 1.f;
		if (pos.x >= rt.right)
			pos.x -= 1.f;

		speed = -speed;
	}
}

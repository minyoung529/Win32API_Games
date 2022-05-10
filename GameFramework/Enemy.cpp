#include "Enemy.h"

Enemy::Enemy()
	:Object(FPOINT{}, OBJECTSIZE{})
	, speed(50.f)
	, collider{}
	, isCollision(false)
{
	scale = 1.f;
}

Enemy::Enemy(FPOINT pos, OBJECTSIZE size, float scale, float speed)
	:Object(pos, size)
	, speed(speed)
	, collider{}
	, isCollision(false)
{
	this->scale = scale;
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
	if (pos.x < 0 || collider.right > SCREEN_WIDTH)
		speed = -speed;

	pos.x += speed * deltaTime;
	UpdateCollider();
}

void Enemy::Render(HDC hdc, float deltaTime)
{
	enemyImage.DrawBitmap(hdc, (int)pos.x, (int)pos.y,
		(int)(size.width * scale), (int)(size.height * scale));

	SelectObject(hdc, GetStockObject(NULL_BRUSH));
	Rectangle(hdc, collider.left, collider.top,
		collider.right, collider.bottom);
}

void Enemy::Release()
{
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

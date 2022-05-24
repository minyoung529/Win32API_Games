#include "Bullet.h"
#include "EnemyManager.h"

Bullet::Bullet()
	: Object(FPOINT{}, OBJECTSIZE{}), speed(400.f)
{
}

Bullet::Bullet(FPOINT pos, OBJECTSIZE size, float speed)
	: Object(pos, size)
	, speed(speed)
{
}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
	bulletImage.Load(TEXT("Data/bullet.bmp"));

	size.width = bulletImage.GetBitmapInfo().bmWidth;
	size.height = bulletImage.GetBitmapInfo().bmHeight;

}

void Bullet::Update(float deltaTime)
{
	pos.y -= deltaTime * speed;

}

void Bullet::Render(HDC hdc, float deltaTime)
{
	bulletImage.DrawBitmap(hdc, (int)pos.x, (int)pos.y);
}

void Bullet::Release()
{
	bulletImage.Release();
}

bool Bullet::IsValid()
{
	return (pos.y > 0);
}

bool Bullet::IsCollision()
{
	RECT tempRect;

	collider.left = pos.x;
	collider.right = pos.x + (int)(size.width * scale);
	collider.top = pos.y;
	collider.bottom = pos.y + (int)(size.height * scale);

	if (EnemyManager::Instance()->IsCollision(&tempRect, &collider))
		return true;
	
	return false;
}
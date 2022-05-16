#include "EnemyBullet.h"

EnemyBullet::EnemyBullet()
	: Object(FPOINT{}, OBJECTSIZE{}), speed(100.f)
{
}

EnemyBullet::EnemyBullet(FPOINT pos, OBJECTSIZE size, float speed)
	: Object(pos, size)
	, speed(speed)
	, angle(0.f)
	, targetPoint{}
{
}

EnemyBullet::EnemyBullet(FPOINT pos, OBJECTSIZE size, float speed, FPOINT targetPos)
	: Object(pos, size)
	, speed(speed)
	, angle(0.f)
	, targetPoint(targetPos)
{
	float x = targetPos.x - pos.x;
	float y = targetPoint.y - pos.y;

	angle = atan2(y, x);
}

EnemyBullet::EnemyBullet(FPOINT pos, OBJECTSIZE size, float speed, float angle)
	: Object(pos, size)
	, speed(speed)
	, angle(angle)
	, targetPoint{}
{
}

EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::Init()
{
	bulletImage.Load(TEXT("Data/enemybullet.bmp"));
	size.width = bulletImage.GetBitmapInfo().bmWidth;
	size.height = bulletImage.GetBitmapInfo().bmHeight;
	
	rect.left = (int)pos.x;
	rect.right = pos.x + size.width;
	rect.top = (int)pos.y;
	rect.bottom = pos.y + size.height;
}

void EnemyBullet::Update(float deltaTime)
{
	pos.x += cosf(angle) * speed * deltaTime;
	pos.y += sinf(angle) * speed * deltaTime;
}

void EnemyBullet::Render(HDC hdc, float deltaTime)
{
	bulletImage.DrawBitmap(hdc, (int)pos.x, (int)pos.y);
}

void EnemyBullet::Release()
{
	bulletImage.Release();
}

bool EnemyBullet::IsValid()
{
	RECT rt;
	GetClientRect(engine->GetWndHandle(), &rt);

	return PtInRect(&rt, POINT{ (int)pos.x, (int)pos.y });
}

bool EnemyBullet::IsCollision(RECT* targetRect)
{
	RECT* tempRect = nullptr;

	rect.left = (int)pos.x;
	rect.right = pos.x + size.width;
	rect.top = (int)pos.y;
	rect.bottom = pos.y + size.height;

	if (IntersectRect(tempRect, &rect, targetRect))
	{
		return true;
	}

	return false;
}
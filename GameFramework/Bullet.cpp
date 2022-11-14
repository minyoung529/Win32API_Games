#include "pch.h"
#include "Bullet.h"
#include "TimeManager.h"

Bullet::Bullet()
	: m_fDir(1.f)

{
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	Vector2	vPos = GetPos();
	vPos.y += 600.f * FDT * m_fDir;
	SetPos(vPos);
}

void Bullet::Render(HDC hdc)
{
	Vector2 position = GetPos();
	Vector2 scale = GetScale();

	Ellipse
	(
		hdc,
		(int)(position.x - scale.x / 2.f),
		(int)(position.y - scale.y / 2.f),
		(int)(position.x + scale.x / 2.f),
		(int)(position.y + scale.y / 2.f)
	);

	SetScale(scale);
}

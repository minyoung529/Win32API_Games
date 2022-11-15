#include "pch.h"
#include "Bullet.h"
#include "TimeManager.h"

Bullet::Bullet()
	: m_ftheta(M_PI / 4.f)
	, m_vDir(Vector2(1.f, 1.f))

{
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	Vector2	vPos = GetPos();
	vPos.x += 600.f * FDT * m_vDir.x;
	vPos.y += 600.f * FDT * m_vDir.y;
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

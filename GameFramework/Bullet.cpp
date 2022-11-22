#include "pch.h"
#include "Bullet.h"
#include "TimeManager.h"
#include "PathManager.h"
#include "Image.h"
#include "ResourceManager.h"

Bullet::Bullet()
	: m_ftheta(M_PI / 4.f)
	, m_vDir(Vector2(1.f, 1.f))
	, m_pImage(nullptr)

{
	m_pImage = ResourceManager::GetInst()->ImgLoad(L"BulletImg", L"Image\\Bullet.bmp");
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
	int width = (int)m_pImage->GetWidth();
	int height = (int)m_pImage->GetHeight();
	Vector2 pos = GetPos();

	TransparentBlt
	(
		hdc,
		(int)(pos.x - (float)(width / 2)),
		(int)(pos.y - (float)(height / 2)),
		width, height,
		m_pImage->GetDC(),
		0, 0, width, height, RGB(255, 0, 255)
	);
}

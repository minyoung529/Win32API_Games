#include "pch.h"
#include "Monster.h"
#include "TimeManager.h"

Monster::Monster()
	: m_fSpeed(100.f)
	, m_fMaxDistance(50.f)
	, m_vCenterPos(Vector2(0, 0))
	, m_fDir(1.f)
{
	CreateCollider();
}

Monster::~Monster()
{
}

void Monster::Update()
{
	Vector2 vCurPos = GetPos();
	vCurPos.x += m_fSpeed * FDT * m_fDir;

	float fDist = abs(m_vCenterPos.x - vCurPos.x) - m_fMaxDistance;

	if (fDist > 0.f)
	{
		m_fDir *= -1.f;
		vCurPos.x += fDist * m_fDir;
	}

	SetPos(vCurPos);
}

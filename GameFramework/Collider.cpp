#include "pch.h"
#include "Collider.h"
#include "Object.h"
#include "SelectGDI.h"

UINT Collider::g_iNextID = 0;


Collider::Collider()
	: m_pOwner(nullptr)
	, m_id(g_iNextID++)
{}

Collider::~Collider()
{}

Collider::Collider(const Collider& origin)
	: m_pOwner(origin.m_pOwner)
	, m_vOffsetPos(origin.m_vOffsetPos)
	, m_vScale(origin.m_vScale)
	, m_id(g_iNextID++)
{}


void Collider::FinalUpdate()
{
	Vector2 vObjectPos = m_pOwner->GetPos();
	m_vFinalPos = vObjectPos + m_vOffsetPos;
}

void Collider::Render(HDC hdc)
{
	m_vFinalPos;
	m_vScale;

	SelectGDI penSelector(hdc, PEN_TYPE::GREEN);
	SelectGDI brushSelector(hdc, BRUSH_TYPE::HOLLOW);

	Rectangle(hdc,
		(int)m_vFinalPos.x - m_vScale.x / 2.f,
		(int)m_vFinalPos.y - m_vScale.y / 2.f,
		(int)m_vFinalPos.x + m_vScale.x / 2.f,
		(int)m_vFinalPos.y + m_vScale.y / 2.f);
}

void Collider::EnterCollision(Collider* _pOther)
{
}

void Collider::StayCollision(Collider* _pOther)
{
}

void Collider::ExitCollision(Collider* _pOther)
{
}

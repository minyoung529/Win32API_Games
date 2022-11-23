#include "pch.h"
#include "Collider.h"
#include "Object.h"

void Collider::FinalUpdate()
{
	Vector2 vObjectPos = m_pOwner->GetPos();
	m_vFinalPos = vObjectPos + m_vOffsetPos;
}

void Collider::Render(HDC hdc)
{

}


#include "pch.h"
#include "Object.h"
#include "Collider.h"

Object::Object() :
	m_ptPos{},
	m_ptScale{},
	m_pCollider(nullptr)
{
}

Object::~Object()
{
	if (m_pCollider)
		delete m_pCollider;
}


void Object::Render(HDC hdc)
{
	Vector2 position = GetPos();
	Vector2 scale = GetScale();

	Rectangle
	(
		hdc,
		(int)(position.x - scale.x / 2.f),
		(int)(position.y - scale.y / 2.f),
		(int)(position.x + scale.x / 2.f),
		(int)(position.y + scale.y / 2.f)
	);

	SetScale(scale);
	Component_Render(hdc);
}

void Object::Component_Render(HDC hdc)
{
	if (m_pCollider)
	{
		m_pCollider->Render(hdc);
	}
}

void Object::CreateCollider()
{
	m_pCollider = new Collider;
	m_pCollider->m_pOwner = this;
}

void Object::FinalUpdate()
{
	if (m_pCollider)
		m_pCollider->FinalUpdate();
}
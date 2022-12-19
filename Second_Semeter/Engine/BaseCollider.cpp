#include "pch.h"
#include "BaseCollider.h"

BaseCollider::BaseCollider(ColliderType type)
	: Component(COMPONENT_TYPE::COLLIDER)
	, m_colliderType(type)
{
}

BaseCollider::~BaseCollider()
{
}

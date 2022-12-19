#pragma once
#include "Component.h"

enum class ColliderType
{
	Sphere,
};

class BaseCollider : public Component
{
public:
	BaseCollider(ColliderType type);
	virtual ~BaseCollider();

	virtual bool Intersects(Vec4 rayOrigin, Vec4 rayDir, OUT float& distance) = 0;

private:
	ColliderType m_colliderType = {};
};
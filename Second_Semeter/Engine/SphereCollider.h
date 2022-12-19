#pragma once
#include "BaseCollider.h"
class SphereCollider : public BaseCollider
{
public:
	SphereCollider();
	virtual ~SphereCollider();

	virtual void FinalUpdate() override;

	virtual bool Intersects(Vec4 rayOrigin, Vec4 rayDir, OUT float& distance) override;

private:
	float m_radius = 0.5f;
	Vec3 m_center = Vec3(0, 0, 0);

	BoundingSphere m_boundingSphere;
};


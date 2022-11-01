#pragma once
#include "Component.h"

class Transform : public Component
{
public:
	Transform();
	virtual ~Transform();

	void SetPosition(const Vec3& t) { m_transform.offset = t; }
	Vec3 GetPosition() { return m_transform.offset; }

	void PushData();

private:
	TransformParams m_transform = {};
};


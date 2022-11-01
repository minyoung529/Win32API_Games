#include "pch.h"
#include "Transform.h"
#include "engine.h"

Transform::Transform() : Component(COMPONENT_TYPE::TRANSFORM)
{
	m_transform.offset = {};
}

Transform::~Transform()
{
}

void Transform::PushData()
{
	CONST_BUFFER(CONSTANT_BUFFER_TYPE::TRANSFORM)->PushData(&m_transform, sizeof(m_transform));
}

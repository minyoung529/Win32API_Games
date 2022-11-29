#include "pch.h"
#include "Light.h"
#include "Transform.h"

Light::Light() : Component(COMPONENT_TYPE::LIGHT)
{
}

Light::~Light()
{
}

void Light::FinalUpdate()
{
	m_lightInfo.position = GetTransform()->GetWorldPosition();
}

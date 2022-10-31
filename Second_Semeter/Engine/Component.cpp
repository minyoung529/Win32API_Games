#include "pch.h"
#include "Component.h"
#include "GameObject.h"

Component::Component(COMPONENT_TYPE type) : m_type(type)
{
}

Component::~Component()
{
}

shared_ptr<GameObject> Component::GetGameObject()
{
	return m_gameObject.lock();
}

shared_ptr<Transform> Component::GetTransform()
{
	return m_gameObject.lock()->GetTransform();
}

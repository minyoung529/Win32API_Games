#include "GameObject.h"
#include "pch.h"
#include "GameObject.h"
#include "Transform.h"
#include "MonoBehaviour.h"
#include "Component.h"

GameObject::GameObject() : Object(OBJECT_TYPE::GAMEOBJECT)
{
}

GameObject::~GameObject()
{
}

void GameObject::Init()
{
}

void GameObject::AddComponent(shared_ptr<Component> component)
{
	component->SetGameObject(shared_from_this());
	uint8 index = static_cast<uint8>(component->GetType());

	// component
	if (index < FIXED_COMPONENT_COUNT)
	{
		m_components[index] = component;
	}
	// monobehaviour
	else
	{
		m_scripts.push_back(dynamic_pointer_cast<MonoBehaviour>(component));
	}
}

void GameObject::Awake()
{
	for (shared_ptr<Component>& component : m_components)
	{
		if (component)
			component->Awake();
	}

	for (shared_ptr<MonoBehaviour>& script : m_scripts)
	{
		if (script)
			script->Awake();
	}
}

void GameObject::Start()
{
	for (shared_ptr<Component>& component : m_components)
	{
		if (component)
			component->Start();
	}

	for (shared_ptr<MonoBehaviour>& script : m_scripts)
	{
		if (script)
			script->Start();
	}
}

void GameObject::Update()
{
	for (shared_ptr<Component>& component : m_components)
	{
		if (component)
			component->Update();
	}

	for (shared_ptr<MonoBehaviour>& script : m_scripts)
	{
		if (script)
			script->Update();
	}
}

void GameObject::LateUpdate()
{
	for (shared_ptr<Component>& component : m_components)
	{
		if (component)
			component->LateUpdate();
	}

	for (shared_ptr<MonoBehaviour>& script : m_scripts)
	{
		if (script)
			script->LateUpdate();
	}
}

void GameObject::FinalUpdate()
{
	for (shared_ptr<Component>& component : m_components)
	{
		if (component)
			component->FinalUpdate();
	}
}

void GameObject::Render()
{
	for (shared_ptr<Component>& component : m_components)
	{
		if (component)
			component->Render();
	}

	for (shared_ptr<MonoBehaviour>& script : m_scripts)
	{
		if (script)
			script->Render();
	}
}

shared_ptr<Transform> GameObject::GetTransform()
{
	uint8 index = static_cast<uint8>(COMPONENT_TYPE::TRANSFORM);
	return static_pointer_cast<Transform>(m_components[index]);
}

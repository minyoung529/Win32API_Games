#pragma once
#include "Component.h"
#include "Object.h"

class MonoBehaviour;
class Transform;

class GameObject : public Object, public enable_shared_from_this<GameObject>
{
public:
	GameObject();
	virtual ~GameObject();

	void Init();
	void AddComponent(shared_ptr<Component> component);

public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();
	void Render();

public:
	shared_ptr<Transform> GetTransform();

private:
	// ม฿บน X
	array<shared_ptr<Component>, FIXED_COMPONENT_COUNT> m_components;
	vector<shared_ptr<MonoBehaviour>> m_scripts;
};


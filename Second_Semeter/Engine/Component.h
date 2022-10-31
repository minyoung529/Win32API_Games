#pragma once

class Transform;
class GameObject;

enum class COMPONENT_TYPE : uint8
{
	TRANSFORM,
	MESHRENDERER,
	// ._.
	MONOBEHAVIOUR,
	END
};

enum
{
	FIXED_COMPONENT_COUNT = static_cast<uint8>(COMPONENT_TYPE::END) - 1
};

class Component
{
public:
	Component(COMPONENT_TYPE type);
	virtual ~Component();

public:
	virtual void Awake() {}
	virtual void Start() {}
	virtual void Update() {}
	virtual void LateUpdate() {}
	virtual void Render() {}

public:
	COMPONENT_TYPE GetType() { return m_type; }
	bool IsValid() { return m_gameObject.expired() == false; }
	shared_ptr<GameObject> GetGameObject();
	shared_ptr<Transform> GetTransform();

private:
	friend class GameObject;
	void SetGameObject(shared_ptr<GameObject> gameObject) { m_gameObject = gameObject; }

protected:
	COMPONENT_TYPE m_type;
	weak_ptr<GameObject> m_gameObject;
};
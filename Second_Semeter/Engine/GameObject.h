#pragma once
#include "Component.h"
#include "Object.h"

class MonoBehaviour;
class Transform;
class Camera;
class Light;
class MeshRenderer;
class Terrain;
class BaseCollider;

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
	shared_ptr<Component> GetFixedComponent(COMPONENT_TYPE type);

	shared_ptr<Transform> GetTransform();
	shared_ptr<MeshRenderer> GetMeshRenderer();
	shared_ptr<Camera> GetCamera();
	shared_ptr<Light> GetLight();
	shared_ptr<Terrain> GetTerrain();
	shared_ptr<BaseCollider> GetCollider();

	void SetCheckFrustum(bool checkFrustNum) { m_checkFrustum = checkFrustNum; }
	bool GetCheckFrustum() { return m_checkFrustum; }
	void SetLayerIndex(uint8 layer) { m_layerIndex = layer; }
	uint8 GetLayerIndex() { return m_layerIndex; }

private:
	array<shared_ptr<Component>, FIXED_COMPONENT_COUNT>	m_components;
	vector<shared_ptr<MonoBehaviour>> m_scripts;

	bool m_checkFrustum = true;
	uint8 m_layerIndex = 0;
};


#pragma once
class GameObject;

class Scene
{
public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();
	void Render();

private:
	void PushLightData();

public:
	void AddGameObject(shared_ptr<GameObject> gameObject);
	void RemoveGameObject(shared_ptr<GameObject> gameObject);

	const vector<shared_ptr<GameObject>>& GetGameObjects() { return m_gameObjects; }
	shared_ptr<class Camera> GetMainCamera();

private:
	vector<shared_ptr<GameObject>> m_gameObjects;
	vector<shared_ptr<class Camera>> m_cameras;
};
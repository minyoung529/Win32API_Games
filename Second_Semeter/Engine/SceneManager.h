#pragma once

class Scene;

class SceneManager
{
	DECLARE_SINGLE(SceneManager);

public:
	void Update();
	void Render();

public:
	void LoadScene(wstring sceneName);
	void RegisterScene(wstring sceneName, shared_ptr<Scene> scene);

public:
	shared_ptr<Scene> GetActiveScene() { return m_activeScene; }

private:
	shared_ptr<Scene>				m_activeScene;
	map<wstring, shared_ptr<Scene>> m_sceneContainer;
};


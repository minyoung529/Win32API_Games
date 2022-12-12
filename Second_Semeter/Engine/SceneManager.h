#pragma once

enum
{
	MAX_LAYER = 32
};

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

	void SetLayerName(uint8 index, const wstring& name);
	uint8 LayerNameToIndex(const wstring& name);
	const wstring& IndexToLayerName(uint8 index) { return m_layerNames[index]; }

private:
	shared_ptr<Scene>				m_activeScene;
	map<wstring, shared_ptr<Scene>> m_sceneContainer;

	array<wstring, MAX_LAYER>	m_layerNames;
	map<wstring, uint8 >		m_layerIndex;
};


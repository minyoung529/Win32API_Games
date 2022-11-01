#pragma once
class GameObject;

class Game
{
public:
	void Init(const WindowInfo& window);
	void Update();
	void Render();
	void Release();

private:
	shared_ptr<class Scene> m_sampleScene;
};


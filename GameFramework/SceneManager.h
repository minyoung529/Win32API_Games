#pragma once

class Scene;

class SceneManager
{
public:
	SINGLE(SceneManager);

private:
	SceneManager();
	~SceneManager();

private:
	Scene* m_arrScene[(UINT)SCENE_TYPE::END];	// ¾À ¸ñ·Ï
	Scene* m_pCurScene;							// ÇöÀç ¾À

public:
	void	Init();
	void	Update();
	void	Render(HDC hdc);

public:
	Scene* GetCurScene() { return m_pCurScene; }
};

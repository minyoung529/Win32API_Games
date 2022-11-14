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
	Scene* m_arrScene[(UINT)SCENE_TYPE::END];	// �� ���
	Scene* m_pCurScene;							// ���� ��

public:
	void	Init();
	void	Update();
	void	Render(HDC hdc);

public:
	Scene* GetCurScene() { return m_pCurScene; }
};

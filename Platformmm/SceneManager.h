#ifndef	  CSCENEMANAGER_H
#define	  CSCENEMANAGER_H

#include "Scene.h"

class CSceneManager
{
public:

	CSceneManager();
	~CSceneManager();

public:
	void					RegisterScene(const std::string& sceneName, CScene* scene);
	void					ReserveChangeScene(const std::string& sceneName);

public:
	void					Init();
	void					Update(float dt);
	void					Render(HDC hdc, float dt);
	void					Release();

private:
	std::map<std::string, CScene*>	m_SceneContainer;

	CScene*					m_ReservedScene;
	CScene*					m_CurrentScene;
};
#endif // CSCENEMANAGER_H
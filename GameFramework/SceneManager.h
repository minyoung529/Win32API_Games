#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Scene.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

public:
	void	Init();
	void	Update(float deltaTime);
	void	Render(HDC hdc, float deltaTime);
	void	Release();

public:
	void	RegisterScene(const std::string& sceneName, Scene* scene);
	void	ReserveChangeScene(const std::string& sceneName);

private:
	std::map<std::string, Scene*> sceneContainer;

	Scene*		reservedScene;
	Scene*		currentScene;
};

#endif
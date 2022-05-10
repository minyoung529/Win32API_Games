#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "Player.h"
#include "Background.h"
#include "EnemyManager.h"

class GameScene : public Scene
{
private:
	Player* player;
	Background* background;

public:
	GameScene();
	virtual ~GameScene();

public:
	void	Init();
	void	Update(float deltaTime);
	void	Render(HDC hdc, float deltaTime);
	void	Release();
};
#endif
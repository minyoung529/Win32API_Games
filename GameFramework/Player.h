#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"
#include "BasisSystem.h"
#include "Bullet.h"

class Player : public Object
{
public:
	Player();
	Player(FPOINT pos, OBJECTSIZE size, float speed);
	~Player();

private:
	InputState		inputState;
	Image			playerImage;
	float			speed;

	list<Bullet*>	bullets;

private:
	void	CreateBullet();
	void	UpdateBullet(float deltaTime);
	void	RenderBullet(HDC hdc, float deltaTime);
	void	ReleaseBullet();

public:
	void	Init();
	void	Update(float deltaTime);
	void	Render(HDC  hdc, float deltaTime);
	void	Release();
};
#endif
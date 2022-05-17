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
	Player(FPOINT pos, OBJECTSIZE size, float speed, float scale);
	~Player();

private:
	InputState		inputState;
	Image			playerImage;
	float			speed;
	float			hp;
	float			maxHp;

	list<Bullet*>	bullets;
	RECT			rect;
	RECT			hpRect;

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

public:
	FPOINT	GetPos() { return FPOINT{ pos.x, pos.y }; }
	FPOINT	GetCenter()
	{
		return FPOINT{	(pos.x + size.width * 0.5f * scale),
						(pos.y + size.height * 0.5f * scale) };
	}
	RECT*	GetRect() { return &rect; }
	void	SetHP(float hp) { this->hp = hp; }
	float	GetHP() { return hp; }
	void	AddHP(float hp) { this->hp += hp; }
};
#endif
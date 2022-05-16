#ifndef ENEMUBULLET_H
#define ENEMUBULLET_H

#include "Object.h"
#include "BasisSystem.h"
#include "BasisSystem.h"

class EnemyBullet : public Object
{
public:
	EnemyBullet();
	EnemyBullet(FPOINT pos, OBJECTSIZE size, float speed);
	EnemyBullet(FPOINT pos, OBJECTSIZE size, float speed, FPOINT targetPos);
	EnemyBullet(FPOINT pos, OBJECTSIZE size, float speed, float angle);
	~EnemyBullet();

public:
	void Init();
	void Update(float deltaTime);
	void Render(HDC hdc, float deltaTime);
	void Release();

public:
	bool IsValid();
	bool IsCollision(RECT* targetRect);

	RECT GetRect() { return rect; }

private:
	float	speed;
	float	angle;
	FPOINT	targetPoint;
	RECT	rect;
	Image	bulletImage;
};

#endif
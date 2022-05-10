#ifndef BULLET_H
#define BULLET_H

#include "Object.h"
#include "BasisSystem.h"

class Bullet : public Object
{
public:
	Bullet();
	Bullet(FPOINT pos, OBJECTSIZE size, float speed);
	~Bullet();

public:
	void Init();
	void Update(float deltaTime);
	void Render(HDC hdc, float deltaTime);
	void Release();

public:
	bool IsValid();
	bool IsCollision();


private:
	Image	bulletImage;
	float	speed;
	RECT	collider;
};
#endif
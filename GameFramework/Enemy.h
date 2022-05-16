#include "Object.h"
#include "BasisSystem.h"
#include "EnemyBullet.h"

class Enemy : public Object
{
public:
	Enemy();
	Enemy(FPOINT pos, OBJECTSIZE size, float scale, float speed);
	Enemy(FPOINT pos, OBJECTSIZE size, float scale, float speed , BULLET_TYPE type);
	~Enemy();

public:
	void Init();
	void Update(float deltaTime);
	void Render(HDC hdc, float deltaTime);
	void Release();

private:
	void UpdateCollider();

public:
	void SetTargetPos(FPOINT pos)
	{
		targetPos = pos;
	}
	FPOINT GetTargetPos()
	{
		return targetPos;
	}

private:
	Image	enemyImage;
	float	speed;
	RECT	collider;
	bool	isCollision;

public: 
	bool	GetCollision();
	void	SetCollision(bool isCollision);
	RECT*	GetRect();

private:
	BULLET_TYPE		bulletType;
	float			regenTime; // ���� �ð�
	float			maxRegen; // ���� �ִ� �ð�
	float			accTime; // �ð� ����
	FPOINT			targetPos;

	vector<EnemyBullet*> bullets;
};

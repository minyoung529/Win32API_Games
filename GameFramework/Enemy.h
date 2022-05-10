#include "Object.h"
#include "BasisSystem.h"

class Enemy : public Object
{
public:
	Enemy();
	Enemy(FPOINT pos, OBJECTSIZE size, float scale, float speed);
	~Enemy();

public:
	void Init();
	void Update(float deltaTime);
	void Render(HDC hdc, float deltaTime);
	void Release();

private:
	void UpdateCollider();

private:
	Image enemyImage;
	float speed;
	RECT collider;
	bool isCollision;

public: 
	bool	GetCollision();
	void	SetCollision(bool isCollision);
	RECT*	GetRect();
};

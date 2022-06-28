#ifndef MONSTER_H
#define MONSTER_H

#include "BasisStd.h"
#include "Animation.h"

enum MONSTER_TYPE
{
	KING_PIG,
	MONSTER_COUNT
};

enum MONSTER_STATE
{
	MONSTER_STATE_NONE = -1,

	RIGHT_IDLE = 0,
	LEFT_IDLE,

	RIGHT_MOVE,
	LEFT_MOVE,

	RIGHT_ATTACK,
	LEFT_ATTACK,

	RIGHT_HIT,
	LEFT_HIT,

	RIGHT_DEAD,
	LEFT_DEAD,

	MONSTER_STATE_COUNT
};

class Monster
{
public:
	Monster() = default;
	~Monster() = default;

public:
	Monster(MONSTER_TYPE type, FPOINT pos, float speed = 10.0f) :
		type(type), pos(pos), speed(speed), scale(1.f), gravity(10.f) {}

public:
	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void Release() = 0;

public:
	virtual void Move(float deltaTime) = 0;
	virtual void SetAnimation(MONSTER_STATE state) = 0;
	virtual void CheckMonsterState() = 0;
	virtual void CheckCollision() = 0;

protected:
	virtual bool IsCollision(RECT* rc1, RECT* rc2)
	{
		bool collision = false;
		RECT temp;
		if (IntersectRect(&temp, rc1, rc2))
		{
			collision = true;
		}
		return collision;
	}

	virtual float Distance(FPOINT pos1, FPOINT pos2)
	{
		float x = pos2.x - pos1.x;
		float y = pos2.y - pos1.y;

		return sqrt(x * x + y + y);
	}

public:
	void SetId(int id) { this->id = id; }
	UINT GetID() { return id; }

	void SetPos(FPOINT pos) { this->pos; }
	FPOINT GetPos() { return pos; }

	void SetCenter(FPOINT center) { this->center = center; }
	FPOINT GetCenter() { return center; }

	void SetSize(OBJSIZE size) { this->size = size; }
	OBJSIZE GetSize() { return size; }

	void SetScale(float scale) { this->scale = scale; }
	float GetScale() { return scale; }

	void SetSpeed(float speed) { this->speed = speed; }
	float GetSpeed() { return speed; }

	void SetGravity(float gravity) { this->gravity = gravity; }
	float GetGravity() { return gravity; }

	void SetIsOnGround(bool isGround) { isOnGround = isGround; }
	bool GetIsOnGround() { return isOnGround; }

	void SetCanMoveLeft(bool canMoveLeft) { this->canMoveLeft = canMoveLeft; }
	bool IsCanMoveLeft() { return canMoveLeft; }

	void SetCanMoveRight(bool canMoveRight) { this->canMoveRight = canMoveRight; }
	bool IsCanMoveRight() { return canMoveRight; }

	bool IsLeft() { return state % 2 == 1; }

	void SetHp(int hp) { this->hp = hp; }
	int GetHp() { return hp; }

	void SetMaxHp(int maxHp) { this->maxHp = maxHp; }
	int GetMaxHp() { return maxHp; }

	void SetType(MONSTER_TYPE type) { this->type = type; }
	MONSTER_TYPE GetType() { return type; }

	void SetState(MONSTER_STATE state) { this->state = state; }
	MONSTER_STATE GetState() { return state; }

protected:
	UINT		id;
	FPOINT		pos;
	FPOINT		center;
	OBJSIZE		size;
	float		scale;
	float		speed;
	int			gravity;

	int			hp;
	int			maxHp;

	bool isOnGround;
	bool canMoveLeft;
	bool canMoveRight;

	MONSTER_TYPE type;

	MONSTER_STATE state;
	MONSTER_STATE stateBefore;

	Animation* ani_Idle;
	Animation* ani_Move;
	Animation* ani_Attack;
	Animation* ani_Hit;
	Animation* ani_Dead;
};
#endif // MONSTER_H
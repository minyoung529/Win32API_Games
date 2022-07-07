#ifndef KING_PIG_H
#define KING_PIG_H

#include "Monster.h"
#include "BasisSys.h"

enum KING_PIG_IMAGE
{
	IDLE,
	MOVE,
	ATTACK,
	HIT,
	DEAD,
	KING_PIG_COUNT
};

class KingPig : public Monster
{
public:
	KingPig() = default;
	~KingPig() = default;

public:
	KingPig(MONSTER_TYPE type, FPOINT pos, float speed = 10.f);

public:
	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	virtual void Move(float deltaTime) override;
	virtual void SetAnimation(MONSTER_STATE state) override;

	virtual void CheckMonsterState() override;
	virtual void CheckCollision() override;

	bool IsAttacking()
	{
		if (state == MONSTER_STATE::LEFT_ATTACK || state == MONSTER_STATE::RIGHT_ATTACK)
			return true;
		return false;
	}

	bool IsHitting()
	{
		if (state == MONSTER_STATE::LEFT_HIT || state == MONSTER_STATE::RIGHT_HIT)
			return true;
		return false;
	}

	bool IsDead()
	{
		if (state == MONSTER_STATE::LEFT_DEAD || state == MONSTER_STATE::RIGHT_DEAD)
			return true;
		return false;

	}

private:
	float traceDistance;
	float deadTime;
	float deadDelayTime;

	Image* currentImage;
	Image imageAnimations[KING_PIG_COUNT];

	void DefineAnimation(Animation*& animation, UINT state, int width, int height, int fps);
};

#endif // KING_PIG_H
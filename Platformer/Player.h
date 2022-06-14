#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"
#include "BasisSys.h"

enum class PLAYER_IMAGE
{
	IDLE,
	MOVE,
	ATTACK,
	THROW,
	HURT,
	JUMP,
	DEAD,
	MOVE_EFFECT,
	ATTACK_EFFECT,
	COUNT
};

enum class PLAYER_STATE
{
	NONE = -1,

	// IDLE
	RIGHT_IDLE,
	LEFT_IDLE,

	// MOVE
	RIGHT_MOVE,
	LEFT_MOVE,

	// ATTACK
	RIGHT_ATTACK,
	LEFT_ATTACK,

	// THROW
	RIGHT_THROW,
	LEFT_THROW,

	// HURT
	RIGHT_HURT,
	LEFT_HURT,

	// JUMP
	RIGHT_JUMP,
	LEFT_JUMP,

	// FALL
	RIGHT_FALL,
	LEFT_FALL,

	// DEAD
	RIGHT_DEAD,
	LEFT_DEAD
};

class Player : public Object
{
public:
	Player();
	Player(FPOINT pos, OBJSIZE size, float speed);
	~Player();

public:
	void Init() override;
	void Update(float deltaTime) override;
	void Render(HDC hdc, float deltaTime) override;
	void Release() override;

public:
	void SetAnimation(PLAYER_STATE state);
	void DefineAnimation(Animation*& animation, UINT state, int width, int height, int fps);
	bool IsLeft() { return (UINT)state % 2 == 1; }
	bool IsAttacking()
	{
		if (state == PLAYER_STATE::LEFT_ATTACK || state == PLAYER_STATE::RIGHT_ATTACK)
			return true;
		return false;
	}

private:
	float			speed;
	float			angle;
	float			gravity;
	float			hp;
	float			maxHp;

	PLAYER_STATE	state;
	PLAYER_STATE	stateBefore;

private:
	InputState inputState;

	Image* imagePlayer;
	Image* imageEffect;
	Image imageAnimation[(UINT) PLAYER_IMAGE::COUNT];

	Animation* ani_Idle;
	Animation* ani_Move;
	Animation* ani_Attack;
	Animation* ani_Throw;
	Animation* ani_Hurt;
	Animation* ani_Jump;
	Animation* ani_Dead;

	Animation* ani_MoveEffect;
	Animation* ani_AttackEffect;
};

#endif
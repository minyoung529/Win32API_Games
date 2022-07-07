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

	bool IsJumping()
	{
		if (state == PLAYER_STATE::LEFT_JUMP || state == PLAYER_STATE::RIGHT_JUMP)
			return true;
		return false;
	}

	bool IsFalling()
	{
		if (state == PLAYER_STATE::LEFT_FALL || state == PLAYER_STATE::RIGHT_FALL)
			return true;
		return false;
	}


	void AddForceX(float x) { pos.x += x; }
	FPOINT GetPos() { return pos; }
	OBJSIZE GetSize() { return size; }
	RECT* GetRect()
	{
		rect.left = pos.x;
		rect.top = pos.y;
		rect.right = pos.x + size.width;
		rect.bottom = pos.y + size.height;

		return &rect;
	}
	RECT* GetAttackRect()
	{
		attackRect.left = pos.x;
		attackRect.top = pos.y;
		attackRect.right = pos.x + effectSize.width;
		attackRect.bottom = pos.y + effectSize.height;

		return &attackRect;
	}

	bool IsMovingRight()
	{
		if (state == PLAYER_STATE::RIGHT_MOVE ||
			((state == PLAYER_STATE::RIGHT_JUMP ||
				state == PLAYER_STATE::RIGHT_FALL) &&
				angle != (float)PI / 2.0f))
			return true;
		return false;
	}

	bool IsMovingLeft()
	{
		if (state == PLAYER_STATE::LEFT_MOVE ||
			((state == PLAYER_STATE::LEFT_JUMP ||
				state == PLAYER_STATE::LEFT_FALL) &&
				angle != (float)PI / 2.0f))
			return true;
		return false;
	}

	bool IsAttacked()
	{
		return isAttacked;
	}

	void SetIsAttacked(bool isAtk)
	{
		if (!isAttacked)
		{
			if (IsLeft())
			{
				SetAnimation(PLAYER_STATE::LEFT_HURT);
			}
			else
			{
				SetAnimation(PLAYER_STATE::RIGHT_HURT);
			}
		}
		isAttacked = isAtk;
	}

	void SetIsOnGround(bool isG) { isOnGround = isG; }
	bool GetIsOnGround() { return isOnGround; }

	void SetCanMoveLeft(bool left) { canMoveLeft = left; }
	bool GetCanMoveLeft() { return canMoveLeft; }

	void SetCanMoveRight(bool right) { canMoveRight = right; }
	bool GetCanMoveRight() { return canMoveRight; }

	void SetCanAttack(bool canAtk) { canAttack = canAtk; }
	bool GetCanAttack() { return canAttack; }

private:
	float			speed;
	float			jumpSpeed;
	float			angle;
	float			gravity;
	float			hp;
	float			maxHp;

	bool			isOnGround;
	bool			canMoveLeft;
	bool			canMoveRight;

	bool			isAttacked;
	float			attackTime;
	float			attackDelayTime;

	bool			canAttack;

	RECT			rect;
	RECT			attackRect;
	FPOINT			effectPos;
	OBJSIZE			effectSize;

	PLAYER_STATE	state;
	PLAYER_STATE	stateBefore;

private:
	InputState inputState;

	Image* imagePlayer;
	Image* imageEffect;
	Image imageAnimation[(UINT)PLAYER_IMAGE::COUNT];

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
#include "Player.h"

Player::Player()
	: Object(FPOINT{ 100,SCREEN_HEIGHT / 2 }, OBJSIZE{ 96,96 }, 1.f)
	, speed(10.f)
	, jumpSpeed(10.0f)
	, angle(PI / 2)
	, gravity(0.f)
	, hp(0.f)
	, maxHp(0.f)
	, ani_MoveEffect(nullptr)
	, ani_AttackEffect(nullptr)
	, state(PLAYER_STATE::NONE)
{
	canMoveLeft = false;
	canMoveRight = false;
	isOnGround = false;
	memset(&inputState, 0, sizeof(InputState));
}

Player::Player(FPOINT pos, OBJSIZE size, float speed)
	: Object(pos, size, 1.f)
	, speed(speed)
	, jumpSpeed(10.0f)
	, angle(PI / 2)
	, gravity(0.f)
	, hp(0.f)
	, maxHp(0.f)
	, ani_MoveEffect(nullptr)
	, ani_AttackEffect(nullptr)
	, state(PLAYER_STATE::NONE)
{
	canMoveLeft = false;
	canMoveRight = false;
	isOnGround = false;
	memset(&inputState, 0, sizeof(InputState));
}

Player::~Player()
{
}

void Player::Init()
{
	imageAnimation[(UINT)PLAYER_IMAGE::IDLE].Load(TEXT("Data/Player/Owlet_Monster_Idle_24.bmp"));
	imageAnimation[(UINT)PLAYER_IMAGE::MOVE].Load(TEXT("Data/Player/Owlet_Monster_Walk_26.bmp"));
	imageAnimation[(UINT)PLAYER_IMAGE::ATTACK].Load(TEXT("Data/Player/Owlet_Monster_Attack2_26.bmp"));
	imageAnimation[(UINT)PLAYER_IMAGE::THROW].Load(TEXT("Data/Player/Owlet_Monster_Throw_24.bmp"));
	imageAnimation[(UINT)PLAYER_IMAGE::HURT].Load(TEXT("Data/Player/Owlet_Monster_Hurt_24.bmp"));
	imageAnimation[(UINT)PLAYER_IMAGE::JUMP].Load(TEXT("Data/Player/Owlet_Monster_Jump_28.bmp"));
	imageAnimation[(UINT)PLAYER_IMAGE::DEAD].Load(TEXT("Data/Player/Owlet_Monster_Death_28.bmp"));

	imageAnimation[(UINT)PLAYER_IMAGE::MOVE_EFFECT].Load(TEXT("Data/Player/Walk_Run_Push_Dust_26.bmp"));
	imageAnimation[(UINT)PLAYER_IMAGE::ATTACK_EFFECT].Load(TEXT("Data/Player/Owlet_Monster_effect_24.bmp"));

	DefineAnimation(ani_Idle, (UINT)PLAYER_IMAGE::IDLE, 4, 2, 10);
	DefineAnimation(ani_Move, (UINT)PLAYER_IMAGE::MOVE, 6, 2, 10);
	DefineAnimation(ani_Attack, (UINT)PLAYER_IMAGE::ATTACK, 6, 2, 10);
	DefineAnimation(ani_Throw, (UINT)PLAYER_IMAGE::THROW, 4, 2, 10);
	DefineAnimation(ani_Hurt, (UINT)PLAYER_IMAGE::HURT, 4, 2, 10);
	DefineAnimation(ani_Jump, (UINT)PLAYER_IMAGE::JUMP, 8, 2, 10);
	DefineAnimation(ani_Dead, (UINT)PLAYER_IMAGE::DEAD, 8, 2, 10);
	DefineAnimation(ani_MoveEffect, (UINT)PLAYER_IMAGE::MOVE_EFFECT, 6, 2, 10);
	DefineAnimation(ani_AttackEffect, (UINT)PLAYER_IMAGE::ATTACK_EFFECT, 4, 2, 10);

	SetAnimation(PLAYER_STATE::RIGHT_IDLE);
	stateBefore = PLAYER_STATE::RIGHT_IDLE;
}

void Player::Update(float deltaTime)
{
	engine->Input.KeyCheck(VK_LEFT, inputState.keyLeft);
	engine->Input.KeyCheck(VK_RIGHT, inputState.keyRight);
	engine->Input.KeyCheck(VK_SPACE, inputState.keySpace);
	engine->Input.KeyCheck('A', inputState.keyA);

	if (inputState.keyLeft == KEY_PUSH)
	{
		if (!(IsJumping() || IsFalling() || IsAttacking()))
		{
			SetAnimation(PLAYER_STATE::LEFT_MOVE);
		}
	}

	if (inputState.keyLeft == KEY_DOWN)
	{
		stateBefore = PLAYER_STATE::LEFT_MOVE;

		if (IsJumping())
		{
			angle = PI / 5 * 3;
			SetAnimation(PLAYER_STATE::LEFT_JUMP);
		}
		if (IsFalling())
		{
			SetAnimation(PLAYER_STATE::LEFT_FALL);
		}
		if (state == PLAYER_STATE::LEFT_MOVE && ani_Move->IsPlay() && canMoveLeft)
		{
			pos.x -= speed * deltaTime;
		}
	}

	if (inputState.keyLeft == KEY_UP)
	{
		stateBefore = PLAYER_STATE::LEFT_IDLE;

		if (isOnGround)
		{
			SetAnimation(PLAYER_STATE::LEFT_IDLE);
		}
		else if (!(IsFalling() || IsJumping() || IsAttacking()))
		{
			SetAnimation(PLAYER_STATE::LEFT_FALL);
			angle = PI / 5 * 3;
			gravity = jumpSpeed + 0.2f;
		}
	}

	if (inputState.keyRight == KEY_PUSH)
	{
		if (!(IsJumping() || IsFalling() || IsAttacking()))
		{
			SetAnimation(PLAYER_STATE::RIGHT_MOVE);
		}
	}

	if (inputState.keyRight == KEY_DOWN)
	{
		stateBefore = PLAYER_STATE::RIGHT_MOVE;
		if (IsJumping())
		{
			angle = PI / 5 * 2;
			SetAnimation(PLAYER_STATE::RIGHT_JUMP);
		}
		if (IsFalling())
		{
			SetAnimation(PLAYER_STATE::RIGHT_FALL);
		}
		if (state == PLAYER_STATE::RIGHT_MOVE && ani_Move->IsPlay() && canMoveRight)
		{
			pos.x += speed * deltaTime;
		}
	}

	if (inputState.keyRight == KEY_UP)
	{
		stateBefore = PLAYER_STATE::RIGHT_IDLE;

		if (isOnGround)
		{
			SetAnimation(PLAYER_STATE::RIGHT_IDLE);
		}

		else if (!(IsFalling() || IsJumping() || IsAttacking()))
		{
			SetAnimation(PLAYER_STATE::RIGHT_FALL);
			angle = PI / 5 * 2;
			gravity = jumpSpeed + 0.2f;
		}
	}

	if (!(IsJumping() || IsFalling()) && !GetIsOnGround())
	{
		pos.y += 3;
	}

	if (inputState.keyA == KEY_PUSH)
	{
		if (!IsAttacking())
		{
			if (IsLeft())
			{
				SetAnimation(PLAYER_STATE::LEFT_ATTACK);
			}
			else
			{
				SetAnimation(PLAYER_STATE::RIGHT_ATTACK);
			}
		}
	}

	if (inputState.keySpace == KEY_PUSH)
	{
		if (IsLeft() && !IsJumping() && !IsFalling() && isOnGround && !IsAttacking())
		{
			stateBefore = state;
			SetAnimation(PLAYER_STATE::LEFT_JUMP);
			gravity = 0;
			isOnGround = false;
			angle = PI / 2;
		}
		else if (!IsLeft() && !IsJumping() && !IsFalling() && isOnGround && !IsAttacking())
		{
			stateBefore = state;
			SetAnimation(PLAYER_STATE::RIGHT_JUMP);
			gravity = 0;
			isOnGround = false;
			angle = PI / 2;
		}
	}

	if (/*!*/(IsJumping() || IsFalling()) && !GetIsOnGround())
	{
		pos.x += cosf(angle) * jumpSpeed;
		pos.y += -sinf(angle) * jumpSpeed + gravity;
		gravity += 0.15f;
	}

	switch (state)
	{
	case PLAYER_STATE::RIGHT_IDLE:
	case PLAYER_STATE::LEFT_IDLE:
		ani_Idle->FrameUpdate(deltaTime);
		break;
	case PLAYER_STATE::RIGHT_MOVE:
	case PLAYER_STATE::LEFT_MOVE:
		ani_Move->FrameUpdate(deltaTime);
		ani_MoveEffect->FrameUpdate(deltaTime);
		break;
	case PLAYER_STATE::RIGHT_ATTACK:
	case PLAYER_STATE::LEFT_ATTACK:
		ani_Attack->FrameUpdate(deltaTime);
		ani_AttackEffect->FrameUpdate(deltaTime);

		if (!ani_Attack->IsPlay())
		{
			SetAnimation(stateBefore);
		}
		break;
	case PLAYER_STATE::RIGHT_THROW:
	case PLAYER_STATE::LEFT_THROW:
		ani_Throw->FrameUpdate(deltaTime);
		break;
	case PLAYER_STATE::RIGHT_HURT:
	case PLAYER_STATE::LEFT_HURT:
		ani_Hurt->FrameUpdate(deltaTime);
		break;
	case PLAYER_STATE::RIGHT_JUMP:
		ani_Jump->FrameUpdate(deltaTime);
		if (gravity > jumpSpeed)
		{
			SetAnimation(PLAYER_STATE::RIGHT_FALL);
		}
		break;
	case PLAYER_STATE::LEFT_JUMP:
		ani_Jump->FrameUpdate(deltaTime);
		if (gravity > jumpSpeed)
		{
			SetAnimation(PLAYER_STATE::LEFT_FALL);
		}
		break;
	case PLAYER_STATE::RIGHT_FALL:
	case PLAYER_STATE::LEFT_FALL:
		ani_Jump->FrameUpdate(deltaTime);
		if (isOnGround)
			SetAnimation(stateBefore);
		break;
	case PLAYER_STATE::RIGHT_DEAD:
	case PLAYER_STATE::LEFT_DEAD:
		ani_Dead->FrameUpdate(deltaTime);
		break;
	default:
		break;
	}
}

void Player::Render(HDC hdc, float deltaTime)
{
	if (!imagePlayer) return;

	switch (state)
	{
	case PLAYER_STATE::RIGHT_IDLE:
	case PLAYER_STATE::LEFT_IDLE:
		imagePlayer->DrawAniRender(hdc, pos.x, pos.y, ani_Idle);
		break;
	case PLAYER_STATE::RIGHT_MOVE:
	case PLAYER_STATE::LEFT_MOVE:
		imageEffect->DrawAniRender(hdc, pos.x, pos.y, ani_MoveEffect);
		imagePlayer->DrawAniRender(hdc, pos.x, pos.y, ani_Move);
		break;
	case PLAYER_STATE::RIGHT_ATTACK:
	case PLAYER_STATE::LEFT_ATTACK:
		imagePlayer->DrawAniRender(hdc, pos.x, pos.y, ani_Attack);
		imageEffect->DrawAniRender(hdc, pos.x, pos.y, ani_AttackEffect);
		break;
	case PLAYER_STATE::RIGHT_THROW:
	case PLAYER_STATE::LEFT_THROW:
		imagePlayer->DrawAniRender(hdc, pos.x, pos.y, ani_Throw);
		break;
	case PLAYER_STATE::RIGHT_HURT:
	case PLAYER_STATE::LEFT_HURT:
		imagePlayer->DrawAniRender(hdc, pos.x, pos.y, ani_Hurt);
		break;
	case PLAYER_STATE::RIGHT_JUMP:
	case PLAYER_STATE::LEFT_JUMP:
	case PLAYER_STATE::RIGHT_FALL:
	case PLAYER_STATE::LEFT_FALL:
		imagePlayer->DrawAniRender(hdc, pos.x, pos.y, ani_Jump);
		break;
	case PLAYER_STATE::RIGHT_DEAD:
	case PLAYER_STATE::LEFT_DEAD:
		imagePlayer->DrawAniRender(hdc, pos.x, pos.y, ani_Dead);
		break;
	default:
		break;
	}

	SelectObject(hdc, GetStockObject(NULL_BRUSH));
	Rectangle(hdc, pos.x, pos.y, pos.x + size.width, pos.y + size.height);
}

void Player::Release()
{
}

void Player::SetAnimation(PLAYER_STATE _state)
{
	if (state == _state)
		return;

	ani_Idle->Stop();
	ani_Move->Stop();
	ani_Attack->Stop();
	ani_Throw->Stop();
	ani_Hurt->Stop();
	ani_Jump->Stop();
	ani_Dead->Stop();

	ani_MoveEffect->Stop();
	ani_AttackEffect->Stop();

	state = _state;

	switch (state)
	{
	case PLAYER_STATE::RIGHT_IDLE:
		ani_Idle->SetPlayFrame(0, 3, false, true);
		ani_Idle->Start();
		imagePlayer = &imageAnimation[(UINT)PLAYER_IMAGE::IDLE];
		break;
	case PLAYER_STATE::LEFT_IDLE:
		ani_Idle->SetPlayFrame(4, 7, true, true);
		ani_Idle->Start();
		imagePlayer = &imageAnimation[(UINT)PLAYER_IMAGE::IDLE];
		break;

	case PLAYER_STATE::RIGHT_MOVE:
		ani_Move->SetPlayFrame(0, 5, false, true);
		ani_Move->Start();

		ani_MoveEffect->SetPlayFrame(0, 5, false, true);
		ani_MoveEffect->Start();

		imagePlayer = &imageAnimation[(UINT)PLAYER_IMAGE::MOVE];
		imageEffect = &imageAnimation[(UINT)PLAYER_IMAGE::MOVE_EFFECT];
		break;
	case PLAYER_STATE::LEFT_MOVE:
		ani_Move->SetPlayFrame(6, 11, true, true);
		ani_Move->Start();

		ani_MoveEffect->SetPlayFrame(6, 11, false, true);
		ani_MoveEffect->Start();

		imagePlayer = &imageAnimation[(UINT)PLAYER_IMAGE::MOVE];
		imageEffect = &imageAnimation[(UINT)PLAYER_IMAGE::MOVE_EFFECT];
		break;

	case PLAYER_STATE::RIGHT_ATTACK:
		ani_Attack->SetPlayFrame(0, 5, false, false);
		ani_Attack->Start();
		imagePlayer = &imageAnimation[(UINT)PLAYER_IMAGE::ATTACK];

		ani_AttackEffect->SetPlayFrame(0, 3, false, false);
		ani_AttackEffect->Start();
		imageEffect = &imageAnimation[(UINT)PLAYER_IMAGE::ATTACK_EFFECT];
		break;
	case PLAYER_STATE::LEFT_ATTACK:
		ani_Attack->SetPlayFrame(6, 11, true, false);
		ani_Attack->Start();
		imagePlayer = &imageAnimation[(UINT)PLAYER_IMAGE::ATTACK];

		ani_AttackEffect->SetPlayFrame(4, 7, false, false);
		ani_AttackEffect->Start();
		imageEffect = &imageAnimation[(UINT)PLAYER_IMAGE::ATTACK_EFFECT];
		break;

	case PLAYER_STATE::RIGHT_THROW:
		ani_Throw->SetPlayFrame(0, 3, false, false);
		ani_Throw->Start();
		imagePlayer = &imageAnimation[(UINT)PLAYER_IMAGE::THROW];

		break;
	case PLAYER_STATE::LEFT_THROW:
		ani_Throw->SetPlayFrame(4, 7, true, false);
		ani_Throw->Start();
		imagePlayer = &imageAnimation[(UINT)PLAYER_IMAGE::THROW];
		break;

	case PLAYER_STATE::RIGHT_HURT:
		ani_Hurt->SetPlayFrame(0, 3, false, false);
		ani_Hurt->Start();
		imagePlayer = &imageAnimation[(UINT)PLAYER_IMAGE::HURT];
		break;
	case PLAYER_STATE::LEFT_HURT:
		ani_Hurt->SetPlayFrame(4, 7, true, false);
		ani_Hurt->Start();
		imagePlayer = &imageAnimation[(UINT)PLAYER_IMAGE::HURT];
		break;

	case PLAYER_STATE::RIGHT_JUMP:
		ani_Jump->SetPlayFrame(3, 3, false, false);
		ani_Jump->Start();
		imagePlayer = &imageAnimation[(UINT)PLAYER_IMAGE::JUMP];
		break;
	case PLAYER_STATE::LEFT_JUMP:
		ani_Jump->SetPlayFrame(12, 12, true, false);
		ani_Jump->Start();
		imagePlayer = &imageAnimation[(UINT)PLAYER_IMAGE::JUMP];
		break;

	case PLAYER_STATE::RIGHT_FALL:
		ani_Jump->SetPlayFrame(5, 5, false, false);
		ani_Jump->Start();
		imagePlayer = &imageAnimation[(UINT)PLAYER_IMAGE::JUMP];
		break;
	case PLAYER_STATE::LEFT_FALL:
		ani_Jump->SetPlayFrame(10, 10, true, false);
		ani_Jump->Start();
		imagePlayer = &imageAnimation[(UINT)PLAYER_IMAGE::JUMP];
		break;

	case PLAYER_STATE::RIGHT_DEAD:
		ani_Dead->SetPlayFrame(0, 7, false, false);
		ani_Dead->Start();
		imagePlayer = &imageAnimation[(UINT)PLAYER_IMAGE::DEAD];
		break;
	case PLAYER_STATE::LEFT_DEAD:
		ani_Dead->SetPlayFrame(8, 15, true, false);
		ani_Dead->Start();
		imagePlayer = &imageAnimation[(UINT)PLAYER_IMAGE::DEAD];
		break;
	default:
		break;
	}
}

void Player::DefineAnimation(Animation*& animation, UINT state, int width, int height, int fps)
{
	animation = new Animation;
	int w = imageAnimation[state].GetBitmap().bmWidth;
	int h = imageAnimation[state].GetBitmap().bmHeight;

	animation->Init(w, h, w / width, h / height);
	animation->SetFPS(fps);
}
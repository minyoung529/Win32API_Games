#pragma once

// ¸ÅÅ©·Î¶û enum class
#define SINGLE(type) static type* GetInst(){ static type mgr; return &mgr; }

#define WINDOW_NAME L"Game_Framework"

#define FDT		TimeManager::GetInst()->GetFDT()
#define DT		TimeManager::GetInst()->GetDT()

#define KEY_CHECK(key,state)	KeyManager::GetInst()->GetKey(key) == state
#define KEY_HOLD(key,state)		KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_TAP(key,state)		KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_AWAY(key,state)		KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_NONE(key,state)		KEY_CHECK(key, KEY_STATE::NONE)

enum class KEY_STATE
{
	NONE,
	TAP,
	HOLD,
	AWAY
};

enum class KEY
{
	LEFT, RIGHT, UP, DOWN,
	Q, W, E, R, T, Y, U, I, O, P,
	A, S, D, F, G, H, J, K, L,
	Z, X, C, V, B, N, M,
	ALT, LSHIFT, CTRL, SPACE,
	ENTER, ESC, LAST
};

enum class GROUP_TYPE
{
	DEFAULT,
	PLAYER,
	MONSTER,
	BULLET,
	END = 30
};

enum class SCENE_TYPE
{
	START,
	SCENE_01,
	SCENE_02,
	TOOL,
	END
};
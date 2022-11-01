#pragma once

// ¸ÅÅ©·Î¶û enum class
#define SINGLE(type) static type* GetInst(){ static type mgr; return &mgr; }

#define WINDOW_NAME L"Game_Framework"

#define FDT		TimeManager::GetInst()->GetFDT()
#define DT		TimeManager::GetInst()->GetDT()

enum class KEY_STATE
{
	NONE,
	DOWN,
	HOLD,
	UP
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
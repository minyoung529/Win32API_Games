#ifndef INPUT_H
#define INPUT_H

#include "BasisStd.h"

enum KEYSTATE
{
	KEY_FREE = 0,
	KEY_PUSH,
	KEY_UP,
	KEY_DOWN,
	KEY_HOLD
};

struct InputState
{
	DWORD	keyUp;
	DWORD	keyDown;
	DWORD	keyLeft;
	DWORD	keyRight;
};

class Input
{
public:
	Input();
	~Input();

public:
	void	Init();
	void	Update();
	void	Release();

public:
	void	KeyCheck(DWORD checkKey, DWORD& stateKey);
	int		ScanToASCII(DWORD scanCode, WORD* result);
};
#endif
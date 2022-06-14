#include "Input.h"

Input::Input()
{
}

Input::~Input()
{
}

void Input::Init()
{

}

void Input::Update()
{

}

void Input::Release()
{
}

// GetAsyncKeyState(ÇØ´ç Å°)

void Input::KeyCheck(DWORD checkKey, DWORD& stateKey)
{
	if (GetAsyncKeyState(checkKey) & 0x8000)
	{
		if (stateKey == KEY_FREE)
			stateKey = KEY_PUSH;

		else
			stateKey = KEY_DOWN;
	}
	else
	{
		if (stateKey == KEY_PUSH || stateKey == KEY_DOWN)
			stateKey = KEY_UP;

		else
			stateKey = KEY_FREE;
	}
}

int Input::ScanToASCII(DWORD scanCode, WORD* result)
{
	static HKL layout = GetKeyboardLayout(scanCode);
	static BYTE State[256];

	if (GetKeyboardState(State) == FALSE)
		return 0;

	UINT vk = MapVirtualKeyEx(scanCode, 1, layout);

	return ToAsciiEx(vk, scanCode, State, result, 0, layout);
}

//WORD usValue
//int iKey = ScanToASCII(VK_LBUTTON, &usValue)
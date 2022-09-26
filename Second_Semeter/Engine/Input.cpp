#include "pch.h"
#include "Input.h"

void Input::Init(HWND hWnd)
{
	this->hWnd = hWnd;
	states.resize(KEY_TYPE_COUNT, KEY_STATE::NONE);
}

void Input::Update()
{
	HWND hWnd = ::GetActiveWindow();

	if (this->hWnd != hWnd)
	{
		for (uint32 key = 0; key < KEY_TYPE_COUNT; key++)
		{
			states[key] = KEY_STATE::NONE;
		}

		return;
	}

	for (uint32 key = 0; key < KEY_TYPE_COUNT; key++)
	{
		// 키가 눌려있으면 true

		if (GetAsyncKeyState(key) & 0x8000)
		{
			KEY_STATE& state = states[key];

			// 이전이 누른 적이 있으면
			if (state == KEY_STATE::PRESS || state == KEY_STATE::DOWN)
			{
				state = KEY_STATE::PRESS;
			}
			else
			{
				state = KEY_STATE::DOWN;
			}
		}
		else
		{
			KEY_STATE& state = states[key];

			if (state == KEY_STATE::PRESS || state == KEY_STATE::DOWN)
			{
				state = KEY_STATE::UP;
			}
			else
			{
				state = KEY_STATE::NONE;
			}
		}
	}

	GetCursorPos(&mousePos);
	ScreenToClient(hWnd, &mousePos);
}
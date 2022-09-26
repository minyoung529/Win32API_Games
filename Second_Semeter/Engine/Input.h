#pragma once

enum class KEY_TYPE
{
	UP = VK_UP,
	DOWN = VK_DOWN,
	LEFT = VK_LEFT,
	RIGHT = VK_RIGHT,

	W = 'W',
	A = 'A',
	S = 'S',
	D = 'D',

	LBUTTON = VK_LBUTTON,
	RBUTTON = VK_RBUTTON
};

enum class KEY_STATE
{
	NONE,
	PRESS,
	DOWN,
	UP,
	END
};

enum
{
	KEY_TYPE_COUNT = static_cast<int32>(UINT8_MAX),
	KEY_STATE_COUNT = static_cast<int32>(KEY_STATE::END),
};

class Input
{
public:
	void Init(HWND hWnd);
	void Update();

public:
	bool GetButton(KEY_TYPE key) { return (GetState(key) == KEY_STATE::PRESS); }
	bool GetButtonDown(KEY_TYPE key) { return (GetState(key) == KEY_STATE::DOWN); }
	bool GetButtonUp(KEY_TYPE key) { return (GetState(key) == KEY_STATE::UP); }

	const POINT& GetMousePos() { return mousePos; }

private:
	inline KEY_STATE GetState(KEY_TYPE key) { return states[static_cast<uint8>(key)]; }

private:
	HWND hWnd;
	vector<KEY_STATE> states;
	POINT mousePos = {};
};


#include "BInput.h"


BInput::BInput()
{
}


BInput::~BInput()
{
}

void BInput::Init()
{
	m_IsKey = FALSE;
	memset(&m_byKey, 0, sizeof(BYTE)* 256);
	memset(&m_byOldKey, 0, sizeof(BYTE)* 256);
}

void BInput::Update()
{
}

void BInput::Release()
{
}

//GetAsyncKeyState(해당키) 는 키가 눌려진 시점에 0x8000 값을 리턴해주고
//키가 눌려 있었다면 0x0001 값을 리턴한다.
void BInput::KeyCheck(DWORD dwCheckKey, DWORD& dwStateKey)
{
	if (GetAsyncKeyState(dwCheckKey) & 0x8000)
	{
		if (dwStateKey == KEY_FREE)
			dwStateKey = KEY_PUSH;			// 눌렸을때
		else
			dwStateKey = KEY_DOWN;			// 추가사항     
	}
	else
	{
		if (dwStateKey == KEY_PUSH || dwStateKey == KEY_DOWN)
			dwStateKey = KEY_UP;			// 눌린후
		else
			dwStateKey = KEY_FREE;
	}
}

int BInput::ScanToASCII(DWORD scancode, WORD* result)
{
	static HKL layout = GetKeyboardLayout(0);
	static BYTE State[256];

	if (GetKeyboardState(State) == FALSE)
		return 0;

	UINT vk = MapVirtualKeyEx(scancode, 1, layout);
	return ToAsciiEx(vk, scancode, State, result, 0, layout);
}
//WORD usValue;
//int iKey = ScanToASCII(VK_LBUTTON, &usValue);
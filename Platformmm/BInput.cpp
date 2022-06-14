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

//GetAsyncKeyState(�ش�Ű) �� Ű�� ������ ������ 0x8000 ���� �������ְ�
//Ű�� ���� �־��ٸ� 0x0001 ���� �����Ѵ�.
void BInput::KeyCheck(DWORD dwCheckKey, DWORD& dwStateKey)
{
	if (GetAsyncKeyState(dwCheckKey) & 0x8000)
	{
		if (dwStateKey == KEY_FREE)
			dwStateKey = KEY_PUSH;			// ��������
		else
			dwStateKey = KEY_DOWN;			// �߰�����     
	}
	else
	{
		if (dwStateKey == KEY_PUSH || dwStateKey == KEY_DOWN)
			dwStateKey = KEY_UP;			// ������
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
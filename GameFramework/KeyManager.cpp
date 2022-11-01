#include "pch.h"
#include "KeyManager.h"

int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN,
	'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
	'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
	'Z', 'X', 'C', 'V', 'B', 'N', 'M',
	VK_MENU, VK_LSHIFT, VK_CONTROL, VK_SPACE,
	VK_RETURN, VK_ESCAPE
};

KeyManager::KeyManager()
{
}

KeyManager::~KeyManager()
{
}

void KeyManager::Init()
{
	for (int i = 0; i < (int)KEY::LAST; i++)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
}

void KeyManager::Update()
{
}
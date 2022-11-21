#include "pch.h"
#include "PathManager.h"
#include "Core.h"

PathManager::PathManager()
	: m_szResPath(L"")
{
}

PathManager::~PathManager()
{
}

void PathManager::Init()
{
	GetCurrentDirectory(255, m_szResPath);

	// ��� Ȯ�ο�
	// SetWindowText(Core::GetInst()->GetHwndHandle(), m_szResPath);

	int length = wcslen(m_szResPath);

	// ���� ����
	for (int i = length - 1; i >= 0; i--)
	{
		if (m_szResPath[i] == '\\')
		{
			m_szResPath[i] = '\0';
			break;
		}
	}

	wcscat_s(m_szResPath, 255, L"\\bin\\Res\\");

	 SetWindowText(Core::GetInst()->GetHwndHandle(), m_szResPath);

}

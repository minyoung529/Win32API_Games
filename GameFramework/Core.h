#pragma once
#include "BWindow.h"

// ���� �̱���
/* �̱��� 1
class Core
{
private:
	static Core* g_pInst;

public:
	static Core* GetInst()
	{
		if (g_pInst == nullptr)
		{
			g_pInst = new Core;
		}

		return g_pInst;
	}

	static void Release()
	{
		delete g_pInst;
		g_pInst = nullptr;
	}

	// �ٸ� ������ ��������� �ʴ´�!
private:
	Core();
	~Core();
};
*/

// ���� �̱���
/* 2��° �̱��� */
class Core : public BWindow
{
public:
	SINGLE(Core);
	
private:
	Core();
	~Core();

private:
	POINT	m_ptResolution;	// ���� ������ �ػ�
	HDC		m_hdc;				// ���� �����쿡 Draw�� DC


public:
	int		Init(HWND hWnd, POINT ptResolution);
	void	Progress();

private:
	void	Update();
	void	Render();
};
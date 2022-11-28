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
	SINGLE(Core)
	
private:
	Core();
	~Core();

private:
	POINT		m_ptResolution;	// ���� ������ �ػ�
	HDC			m_hdc;				// ���� �����쿡 Draw�� DC
	HDC			m_memDC;
	HBITMAP		m_hBit;
	HBRUSH		m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN		m_arrPen[(UINT)PEN_TYPE::GREEN];

public:
	const HWND&			GetHwndHandle() { return m_hWnd; }
	const HINSTANCE&	GetHInstanceHandle() { return m_hInstnace; }
	POINT& GetResolution() { return m_ptResolution; }
	const HDC& GetMainDC() { return m_hdc; }
	
	HBRUSH GetBrush(BRUSH_TYPE _eType)
	{
		return m_arrBrush[(UINT)_eType];
	}
	
	HPEN GetPen(PEN_TYPE _eType)
	{
		return m_arrPen[(UINT)_eType];
	}


public:
	int				Init(HWND hWnd, POINT ptResolution);
	void			Progress();
	void			CreateBrushPen();

private:
	virtual void	Update();
	virtual void	Render();
};
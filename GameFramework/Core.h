#pragma once
#include "BWindow.h"

// 동적 싱글톤
/* 싱글톤 1
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

	// 다른 데에서 만들어지지 않는다!
private:
	Core();
	~Core();
};
*/

// 정적 싱글톤
/* 2번째 싱글톤 */
class Core : public BWindow
{
public:
	SINGLE(Core)
	
private:
	Core();
	~Core();

private:
	POINT		m_ptResolution;	// 메인 윈도우 해상도
	HDC			m_hdc;				// 메인 윈도우에 Draw할 DC
	HDC			m_memDC;
	HBITMAP		m_hBit;

public:
	const HWND&			GetHwndHandle() { return m_hWnd; }
	const HINSTANCE&	GetHInstanceHandle() { return m_hInstnace; }
	POINT& GetResolution() { return m_ptResolution; }
public:
	int				Init(HWND hWnd, POINT ptResolution);
	void			Progress();

private:
	virtual void	Update();
	virtual void	Render();
};
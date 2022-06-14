#include "BEngine.h"

// BEngine�� �������� ó��
BEngine* g_pEngine = NULL;

BEngine::BEngine() 
	: m_llPrevCount{}
	, m_llCurCount{}
	, m_llFrequency{}
	, m_fDT(0.)
	, m_fAcc(0.)
	, m_iCallCount(0)
{
	g_pEngine = this;
	
	m_SceneManager = new CSceneManager;

	// ���� ī��Ʈ
	QueryPerformanceCounter(&m_llPrevCount);
	// �ʴ� ī��Ʈ Ƚ��
	QueryPerformanceFrequency(&m_llFrequency);
}

BEngine::~BEngine()
{
	if (m_SceneManager)
		delete m_SceneManager;
}

void BEngine::Startup()
{
	Init();
	m_InputObject.Init();
	m_SoundObject.Init();
	
	if( m_SceneManager )
		m_SceneManager->Init();
}

void BEngine::MainLoop()
{
	QueryPerformanceCounter(&m_llCurCount);
	// ���� �������� ī���ð� ���� ������ ī���� ���� ���̸� ���Ѵ�.
	m_fDT = (float)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (float)m_llFrequency.QuadPart;

	// ���� ī��Ʈ���� ���簪���� ����
	m_llPrevCount = m_llCurCount;

	++m_iCallCount;
	// dt ����
	m_fAcc += m_fDT;

	if (m_fAcc >= 1.)
	{
		m_iFPS = m_iCallCount;
		m_fAcc = 0;
		m_iCallCount = 0;

		// fps ��¿�
		RenderText(m_iFPS, m_fDT);
	}

	_Update(m_fDT);

	HDC hdc = GetDC(m_hWnd);

	_Render(hdc, m_fDT);

	ReleaseDC(m_hWnd, hdc);	
}

void BEngine::Cleanup()
{
	Release();
	m_InputObject.Release();
	m_SoundObject.Release();

	if (m_SceneManager)
		m_SceneManager->Release();
}

void BEngine::_Update(float dt)
{
	m_InputObject.Update();

	if (m_SceneManager)
		m_SceneManager->Update(dt);
	Update(dt);
}

void BEngine::_Render(HDC hdc, float dt)
{
	HDC hMemDC;
	RECT windowRect;
	HBITMAP bitmap;

	GetClientRect(this->GetWndHandle(), &windowRect);

	hMemDC = CreateCompatibleDC(hdc);
	bitmap = CreateCompatibleBitmap(hdc, windowRect.right, windowRect.bottom);

	SelectObject(hMemDC, bitmap);
	FillRect(hMemDC, &windowRect, (HBRUSH)COLOR_BACKGROUND);

	if (m_SceneManager)
		m_SceneManager->Render(hMemDC, dt);

	Render(hMemDC, dt);

	BitBlt(hdc, 0, 0, windowRect.right, windowRect.bottom, hMemDC, 0, 0, SRCCOPY);

	DeleteObject(bitmap);
	DeleteDC(hMemDC);
}

void BEngine::RenderText(UINT fps, float dt)
{
	static TCHAR szTemp[256];
	swprintf_s(szTemp, TEXT("���Ӽӵ� FPS: %d, DT: %f"), fps, dt);
	SetWindowText(m_hWnd, szTemp);
}

void BEngine::Init()
{
}

void BEngine::Update(float dt)
{	
}

void BEngine::Render(HDC hdc, float dt)
{
}

void BEngine::Release()
{
}
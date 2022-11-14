#include "Game.h"
#include "Define.h"
#include "ToggleManager.h"

Game::Game()
	: m_hWnd(NULL)
	, m_systemTime{}
	, m_radius(0)
	, m_clock(nullptr)
{}

Game::~Game() {}

void Game::Init(HWND hWnd)
{
	m_hWnd = hWnd;

	RECT rt;
	GetClientRect(m_hWnd, &rt);
	int width = rt.right - rt.left;
	int height = rt.bottom - rt.top;

	// ���� �� * 0.4�� ����������
	m_radius = (width > height) ? height * 0.4f : width * 0.4f;

	// �ð� ����
	m_clock = new Clock(m_radius, { (LONG)(width * 0.5f), (LONG)(height * 0.45f) });
	m_clock->Init();

	m_toggleManager = new ToggleManager();
	m_toggleManager->Init(m_clock);

	SetTimer(m_hWnd, TIMER_DEFAULT, 60, nullptr);
	SetTimer(m_hWnd, TIMER_SECOND, 1000, nullptr);
}

void Game::Update()
{
	m_toggleManager->Update(m_hWnd);
}

void Game::Render(HDC hdc)
{
	GetLocalTime(&m_systemTime);

	// �ð� ����ϱ� 
	m_clock->RenderClock(m_systemTime, hdc);
	m_toggleManager->Render(hdc);
}

void Game::Release()
{
	delete m_clock;
}

void Game::UpdatePerSec()
{
	m_clock->PlaySound(m_systemTime);
}
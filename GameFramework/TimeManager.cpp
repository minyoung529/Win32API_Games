#include "pch.h"
#include "TimeManager.h"
#include "Core.h"

TimeManager::TimeManager()
	: m_llCurCount{}
	, m_llprevCount{}
	, m_llFrequency{}
	, m_dDt(0)
	, m_iCallCount(0)
{
}

TimeManager::~TimeManager()
{
}

void TimeManager::Init()
{
	// 현재 카운트의 틱
	QueryPerformanceCounter(&m_llprevCount);

	// 초당 카운트
	QueryPerformanceFrequency(&m_llFrequency);
}

void TimeManager::Update()
{
	// 한 프레임에 걸린 시간 구하기
	QueryPerformanceCounter(&m_llCurCount);
	m_dDt = (double)(m_llCurCount.QuadPart - m_llprevCount.QuadPart) / (double)m_llFrequency.QuadPart;
	m_dAcc += m_dDt;

	m_llprevCount = m_llCurCount;
	++m_iCallCount;

	if (m_dAcc >= 1)
	{
		m_iFps = m_iCallCount;
		m_dAcc = 0;
		m_iCallCount = 0;

		static wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS: %d, DT: %lf", m_iFps, m_dDt);
		SetWindowText(Core::GetInst()->GetHwndHandle(), szBuffer);
	}
}

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
	// ���� ī��Ʈ�� ƽ
	QueryPerformanceCounter(&m_llprevCount);

	// �ʴ� ī��Ʈ
	QueryPerformanceFrequency(&m_llFrequency);
}

void TimeManager::Update()
{
	// �� �����ӿ� �ɸ� �ð� ���ϱ�
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

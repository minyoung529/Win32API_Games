#pragma once
class TimeManager
{
private:
	LARGE_INTEGER m_llprevCount;
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llFrequency;
	double m_dDt;
	double m_dAcc;
	UINT m_iCallCount;
	UINT m_iFps;

public:
	SINGLE(TimeManager);

private:
	TimeManager();
	~TimeManager();

public:
	void Init();
	void Update();

	double GetDT() { return m_dDt; }
	float GetFDT() { return (float)m_dDt; }
};
#pragma once

class Timer
{
public:
	void Init();
	void Update();

public:
	uint32 GetFps() { return m_fps; }
	float GetDeltaTime() { return m_deltaTime; }

private:
	uint64	m_frequency = 0;
	uint64	m_prevCount = 0;
	float	m_deltaTime = 0.0f;

private:
	uint32	m_frameCount = 0;
	float	m_frameTime = 0.0f;
	uint32	m_fps = 0;
};


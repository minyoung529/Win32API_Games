#pragma once
class Timer
{
public:
	void Init();
	void Update();

public:
	uint32 GetFps() { return fps; }
	float GetDeltaTime() { return deltaTime; }

private:
	uint64	frequency = 0;
	uint64	prevCount = 0;
	float	deltaTime = 0.f;

private:
	uint32	frameCount = 0;
	float	frameTime = 0.f;
	uint32	fps = 0;

};
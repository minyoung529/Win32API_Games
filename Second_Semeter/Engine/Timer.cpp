#include "pch.h"
#include "Timer.h"

void Timer::Init()
{
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&frequency));
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&prevCount));
}

void Timer::Update()
{
	uint64 currentCount;
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentCount));

	deltaTime = (currentCount - prevCount) / static_cast<float>(frequency);
	prevCount = currentCount;

	frameCount++;
	frameTime += deltaTime;

	if (frameTime >= 1.f)
	{
		fps = static_cast<uint32>(frameCount);

		frameCount = 0;
		frameTime = 0.f;
	}
}

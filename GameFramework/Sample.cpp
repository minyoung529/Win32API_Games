#include "Sample.h"

Sample::Sample()
{
}

Sample::~Sample()
{
}

void Sample::Init()
{
}

void Sample::Update(float deltaTime)
{
}

void Sample::Render(HDC hdc, float deltaTime)
{
}

void Sample::Release()
{
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	Sample  sampleEngine;
	sampleEngine.Run(hInstance, lpCmdLine, nCmdShow);
	return 0;
}
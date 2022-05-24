#include "Sample.h"
#include "GameScene.h"

Sample::Sample()
{
}

Sample::~Sample()
{
}

void Sample::Init()
{
	if (mSceneManager)
	{
		mSceneManager->RegisterScene("GameScene", new GameScene);
		mSceneManager->ReserveChangeScene("GameScene");
	}
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
#include "Sample.h"

Sample::Sample()
{
}

Sample::~Sample()
{
}

void Sample::Init()
{
	bitmapFile.Load(TEXT("Data/Bitmap.bmp"));
	memset(&inputState, 0, sizeof(inputState));
	posX = 100;
	posY = 100;

	moveSpeed = 50;

	Sound.Play(BackgroundSound);
}

void Sample::Update(float deltaTime)
{
	Input.KeyCheck(VK_LEFT, inputState.keyLeft);
	Input.KeyCheck(VK_RIGHT, inputState.keyRight);
	Input.KeyCheck(VK_DOWN, inputState.keyDown);
	Input.KeyCheck(VK_UP, inputState.keyUp);

	if (inputState.keyLeft == KEY_DOWN)
		posX -= moveSpeed * deltaTime;
	if (inputState.keyRight == KEY_DOWN)
		posX += moveSpeed * deltaTime;
	if (inputState.keyUp == KEY_DOWN)
		posY -= moveSpeed * deltaTime;
	if (inputState.keyDown == KEY_DOWN)
		posY += moveSpeed * deltaTime;
}

void Sample::Render(HDC hdc, float deltaTime)
{
	bitmapFile.DrawBitmap(hdc, posX, posY);
}

void Sample::Release()
{
	bitmapFile.Release();
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
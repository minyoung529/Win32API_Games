#include "EndScene.h"

EndScene::EndScene()
	: startPosition{ 100, 700 }
	, startRect{ }
{
}

EndScene::~EndScene()
{
}

void EndScene::Init()
{
	startPosition = { 100, 700 };
	startRect = { };
	memset(&inputState, 0, sizeof(InputState));

	backgroundImage.Load(TEXT("Data/BG05.bmp"));
	startButtonImage.Load(TEXT("Data/restartbutton.bmp"));

	startRect.left = startPosition.x;
	startRect.right = startRect.left + startButtonImage.GetBitmapInfo().bmWidth;
	startRect.top = startPosition.y;
	startRect.bottom = startRect.top + startButtonImage.GetBitmapInfo().bmHeight;
}

void EndScene::Update(float deltaTime)
{
	if (!engine) return;

	engine->Input.KeyCheck(VK_LBUTTON, inputState.mouseLButton);

	if (inputState.mouseLButton == KEY_PUSH)
	{
		POINT point;
		GetCursorPos(&point);
		ScreenToClient(engine->GetWndHandle(), &point);

		if (PtInRect(&startRect, point))
		{
			if (engine->mSceneManager)
			{
				engine->mSceneManager->ReserveChangeScene("GameScene");
			}
		}
	}
}

void EndScene::Render(HDC hdc, float deltaTime)
{
	backgroundImage.DrawBitmap(hdc, 0, 0);
	startButtonImage.DrawBitmap(hdc, startPosition.x, startPosition.y, 300, 100);
}

void EndScene::Release()
{
	backgroundImage.Release();
	startButtonImage.Release();
}
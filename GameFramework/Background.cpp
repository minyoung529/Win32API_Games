#include "Background.h"

Background::Background()
	: Object(FPOINT{}, OBJECTSIZE{})
	, scrollY(0.f)
	, speed(100.f)
{
}

Background::Background(FPOINT pos, OBJECTSIZE size)
	: Object(pos, size)
	, scrollY(0.f)
	, speed(100.f)
{
}

Background::~Background()
{
}

void Background::Init()
{
	backgroundImage.Load(TEXT("Data/Background1.bmp"));

	size.width = backgroundImage.GetBitmapInfo().bmWidth;
	size.height = backgroundImage.GetBitmapInfo().bmHeight;
}

void Background::Update(float deltaTime)
{
	scrollY += speed * deltaTime;

	if (scrollY >= size.height)
	{
		scrollY -= size.height;
	}
}

void Background::Render(HDC hdc, float deltaTime)
{
	backgroundImage.DrawBitmap(hdc, 0, (int)scrollY);
	backgroundImage.DrawBitmap(hdc, 0, (int)scrollY - size.height);
}

void Background::Release()
{
	backgroundImage.Release();
}
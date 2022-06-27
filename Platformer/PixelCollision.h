#ifndef PIXELCOLLISION_H
#define PIXELCOLLISION_H
#include "Player.h"

class PixelCollision
{
public:
	PixelCollision();
	~PixelCollision();

public:
	void Init();
	void Update(float deltaTime);
	void Render(HDC hdc);
	void Release();

public:
	void SetPlayer(Player* player);

	void SetStage(STAGE stage);
	void PlayerPixelCollision();

private:
	STAGE stage;
	HDC currentMemDC;
	HBITMAP oldBitmap;
	Player* player;

	Image* currentPixel;
	Image imagePixels[STAGE_COUNT];
};

#endif
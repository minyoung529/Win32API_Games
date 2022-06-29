#ifndef PIXELCOLLISION_H
#define PIXELCOLLISION_H
#include "Player.h"
#include "Monster.h"

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
	void SetStage(STAGE stage);

	void SetPlayer(Player* player);
	void PlayerPixelCollision();

	void SetMonsters(vector<Monster*>* monsters) { this->monsters = monsters; };
	void MonstersPixelCollision();

private:
	STAGE stage;
	HDC currentMemDC;
	HBITMAP oldBitmap;
	Player* player;

	Image* currentPixel;
	Image imagePixels[STAGE_COUNT];

	vector<Monster*>* monsters;
};

#endif
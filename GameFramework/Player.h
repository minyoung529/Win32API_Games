#pragma once
#include "Object.h"

class Image;

class Player :  public Object
{
private:
	Image* m_pImage;

public:
	Player();
	~Player();

public:
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	void CreateBullet();
};


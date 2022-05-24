#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Object.h"
#include "BasisSystem.h"

class Background : public Object
{
public:
	Background();
	Background(FPOINT pos, OBJECTSIZE size);
	~Background();

public:
	void Init();
	void Update(float deltaTime);
	void Render(HDC hdc, float deltaTime);
	void Release();

private:
	Image	backgroundImage;
	float	speed;
	float	scrollY;
};
#endif
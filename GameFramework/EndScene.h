#ifndef ENDSCENE_H
#define ENDSCENE_H

#include "Scene.h"
#include "BasisSystem.h"

class EndScene : public Scene
{
public:
	EndScene();
	virtual ~EndScene();

public:
	void	Init();
	void	Update(float deltaTime);
	void	Render(HDC hdc, float deltaTime);
	void	Release();

private:
	InputState	inputState;
	Image		backgroundImage;
	Image		startButtonImage;
	POINT		startPosition;
	RECT		startRect;
};

#endif
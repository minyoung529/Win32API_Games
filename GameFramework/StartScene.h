#ifndef STARTSCENE_H
#define STARTSCENE_H

#include "Scene.h"
#include "BasisSystem.h"

class StartScene : public Scene
{
public:
	StartScene();
	virtual ~StartScene();

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
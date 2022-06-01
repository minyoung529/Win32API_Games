#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "Piece.h"
#include "Block.h"

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();

public:
	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hdc, float deltaTime) override;
	virtual void Release() override;

private:
	bool		gameStart;
	InputState	inputState;

private:
	HBITMAP background;
	RECT	backgroundRect;
	RECT	previewRect;
};
#endif
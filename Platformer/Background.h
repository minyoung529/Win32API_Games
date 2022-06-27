#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Player.h"
#include "BasisSys.h"

enum LOOPIMAGE
{
	LOOPBG1,
	LOOPBG2,
	LOOPBG3,
	LOOPBG4,
	LOOP_COUNT
};

typedef struct tagLOOPINFO
{
	int posX;
	int speed;
} LOOPINFO;

class Background : public Object
{
public:
	Background();
	~Background();

public:
	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hdc, float deltaTime) override;
	virtual void Release() override;
	
public:
	void SetStage(STAGE stage);
	void SetPlayer(Player* p) { player = p; }

private:
	STAGE		stage;
	Player*		player;

	LOOPINFO	loopInfos[LOOP_COUNT];

	Image*	currentBG;
	Image	imageBackgrounds[STAGE_COUNT];
	Image	imageLoopBackground[LOOP_COUNT];
};

#endif // BACKGROUND_H
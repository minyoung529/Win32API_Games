#ifndef BLOCK_H
#define BLOCK_H

#include "Object.h"
#include "BasisSystem.h"

#define POINTNUM	4
#define	DELAYTIME	1000

class Block : public Object
{
private:
	POINT		point[POINTNUM];
	POINT		center;
	PIECE_COLOR color;
	TETRIS_TYPE type;

	int			startTime;
	int			delayTime;
	InputState  inputState;

public:
	Block();
	Block(TETRIS_TYPE type);
	~Block();

public:
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render(HDC hdc);
	virtual void Release();

public:
	int GetGlobalX(const int x) const;
	int GetGlobalY(const int y) const;

	void CreateBlock(TETRIS_TYPE type);
};

#endif // BLOCK_H